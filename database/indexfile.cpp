#include "indexfile.h"

bool ifEmpty(fstream &f)
{
	f.seekp(0, ios::end);
	int pos = f.tellp();
	return (pos == 0);
}

int writePos(fstream &f)
{
	f.seekg(0, ios::end);
	return f.tellg();
}


void write(BPnode &obj, fstream &f)
{
	int isLeaf = obj.getState();
	int num = obj.getNum();
	f.write((char*)&isLeaf, sizeof(int));
	f.write((char*)&num, sizeof(int));
	for (int i = 0; i < num; ++i)
	{
		f.write((char*)&(obj.keys[i]), sizeof(int));
	}
	for (int i = 0; i < num + 1; ++i)
	{
		f.write((char*)&(obj.children[i]), sizeof(int));
	}
	for (int i = 0; i < num; ++i)
	{
		f.write((char*)&(obj.value[i].pos), sizeof(int));
		f.write((char*)&(obj.value[i].length), sizeof(int));
	}
	for (int i = 0; i < num; ++i)
	{
		f.write(&(obj.deleted[i]), sizeof(char));
	}
}

void indexfile::writeRootPos()
{
	f.seekp(0, ios::beg);
	f.write((char*)&rootPos, sizeof(int));
}

bool indexfile::isEmpty()
{
	return empty;
}
void indexfile::openIndexfile(string path, file method)
{
	switch (method)
	{
	case READ_ONLY:
		f.open(path, ios::binary | ios::in);
		if (!f) throw wrongIndexFile();
		break;
	case CREATE:
		f.open(path, ios::binary | ios::out);
		break;
	case READ_AND_WRITE:
	{
		f.open(path, ios::binary | ios::in | ios::out);
		if (!f)
		{
			throw wrongIndexFile();
		}
		if (ifEmpty(f))
		{
			empty = true;
		}
		else
		{
			empty = false;
			f.seekg(0, ios::beg);
			f.read((char*)&rootPos, sizeof(int));
		}
		break;
	}
	}
}

void indexfile::closeIndexfile()
{
	f.close();
}

BPnode indexfile::getBPMessage(int pos)
{
	f.seekg(pos);
	int number;
	int state, parent, num;
	f.read((char*)&state, sizeof(int));
	f.read((char*)&num, sizeof(int));
	BPnode tmp;
	tmp.setPosInFile(pos);
	tmp.setState(state);
	tmp.setNum(num);
	for (int i = 0; i < num; ++i)
	{
		f.read((char*)&number, sizeof(int));
		tmp.keys.push_back(number);
	}
	for (int i = 0; i < num + 1; ++i)
	{
		f.read((char*)&number, sizeof(int));
		tmp.children.push_back(number);
	}
	for (int i = 0; i < num; ++i)
	{
		int pos, length;
		f.read((char*)&pos, sizeof(int));
		f.read((char*)&length, sizeof(int));
		tmp.value.push_back(dataToken(pos, length));
	}
	char *d = new char[num + 1];
	f.read(d, num);
	for (int i = 0; i < num; ++i)
	{
		tmp.deleted[i] = d[i];
	}
	delete d;
	return tmp;
}

int indexfile::writeBPnode(BPnode &obj)
{
	BPnode a = obj;
	int num = obj.getNum();
	int length = 0;
	if (num == 0)
	{
		length = 0;
	}
	else
	{
		length = (3 + num * 4) * 4 + num;
	}
	char *content = new char[INDEX_MAX - length];
	for (int i = 0; i < INDEX_MAX - length -1; ++i)
	{
		content[i] = '\0';
	}
	if (obj.getNum() == 0)
	{
		f.seekp(obj.getPosInFile());
		f.write(content, INDEX_MAX - 1);
		delete content;
		return obj.getPosInFile();
	}
	if (obj.getPosInFile() == -1)
	{
		f.seekp(0, ios::end);
		int pos = f.tellp();
		write(obj, f);
		f.write(content, INDEX_MAX - length - 1);
		delete content;
		return pos;
	}
	else
	{
		f.seekp(obj.getPosInFile());
		write(obj, f);
		f.write(content, INDEX_MAX - length - 1);
		delete content;
		return obj.getPosInFile();
	}
}

BPnode indexfile::search(int key)
{
	BPnode tmp = getBPMessage(rootPos);
	while (!tmp.getState())
	{
		int i = tmp.searchKey(key);
		tmp = getBPMessage(tmp.children[i]);
	}
	return tmp;
}

void indexfile::freshenIndexFile()
{
	writeRootPos();
	for (int i = 0; i < reserve.size(); ++i)
	{
		writeBPnode(reserve[i]);
	}
	reserve.clear();
}

void indexfile::overFlow(BPnode &obj)
{
	path.pop_back();
	if (!obj.isOverFlow())
	{
		freshenIndexFile();
		return;
	}
	int pos = NODE_MAX / 2;
	int num = obj.keys[pos];
	BPnode n;
	if (obj.getState())
	{
		for (int i = pos + 1; i < NODE_MAX + 1; ++i)
		{
			int key = obj.keys[pos + 1];
			int vpos = obj.value[pos + 1].pos;
			int length = obj.value[pos + 1].length;
			n.insert(key, vpos, length);
			obj.remove(key);
		}
	}
	else
	{
		n.children.push_back(obj.children[pos + 1]);
		for (int i = pos + 1; i < NODE_MAX + 1; ++i)
		{
			int key = obj.keys[pos + 1];
			int cpos = obj.children[pos + 2];
			n.insert(key, 0, 0, cpos);
			obj.remove(key);
		}
		obj.remove(num);
	}

	n.setNum(n.keys.size());
	n.setState(obj.getState());
	n.setPosInFile(writePos(f));
	writeBPnode(n);
	int address;
	if (obj.getPosInFile() == rootPos)
	{
		BPnode root;
		root.keys.push_back(num);
		root.setNum(1);
		root.setState(INNER_NODE);
		root.children.push_back(obj.getPosInFile());
		root.children.push_back(n.getPosInFile());
		root.value.push_back(dataToken(0, 0));
		root.setPosInFile(writePos(f));
		rootPos = writeBPnode(root);
		writeRootPos();
		root.setPosInFile(rootPos);
		address = writeBPnode(n);
		n.setPosInFile(address);
		reserve.push_back(obj);
	}
	else
	{
		address = writeBPnode(n);
		n.setPosInFile(address);
		BPnode parent = path[path.size() - 1];
		parent.insert(num, 0, 0, address);
		reserve.push_back(obj);
		if (parent.isOverFlow())
		{
			overFlow(parent);
		}
		else
		{
			reserve.push_back(parent);
		}
	}
	freshenIndexFile();
}


void indexfile::insert(int key, int vpos, int length, int cpos,BPnode &tmp)
{
	if (isEmpty())
	{
		writeRootPos();
		BPnode tmp;
		tmp.insert(key, vpos, length);
		rootPos = writeBPnode(tmp);
		tmp.setPosInFile(rootPos);
		writeRootPos();
		empty = false;
		return;
	}
	if (tmp.HasKey(key))
	{
		tmp.cancelDelete(key, vpos, length);
		writeBPnode(tmp);
		path.clear();
		return;
	}
	tmp.insert(key, vpos, length, cpos);
	path.pop_back();
	path.push_back(tmp);
	if (tmp.isOverFlow())
	{
		overFlow(tmp);
	}
	else
	{
		writeBPnode(tmp);
	}
	path.clear();
}

void indexfile::deleteIdx(int key ,BPnode &obj)
{
	obj.deleteKey(key);
	writeBPnode(obj);
}

void indexfile::setEmpty(int i)
{
	if (i == 1)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}
}

bool indexfile::key(int key,BPnode &tmp)
{
	if (empty)
	{
		return false;
	}
	//BPnode tmp = search(key);
	int i = tmp.searchKey(key);
	if (tmp.HasKey(key))
	{
		return (tmp.deleted[i] == 'y');
	}
	else
	{
		return false;
	}
}

BPnode indexfile::searchInsert(int key)
{
	BPnode tmp = getBPMessage(rootPos);
	path.push_back(tmp);
	while (!tmp.getState())
	{
		int i = tmp.searchKey(key);
		tmp = getBPMessage(tmp.children[i]);
		path.push_back(tmp);
	}
	return tmp;
}

void indexfile::pathClear()
{
	path.clear();
}

void indexfile::recovery(int key, BPnode &obj)
{
	int pos = obj.searchKey(key);
	obj.deleted[pos] = 'y';
	writeBPnode(obj);
}