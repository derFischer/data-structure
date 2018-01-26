#include "BPnode.h"
#define FALSE 0
#define TRUE 1
enum choice{ LEFT , RIGHT };

int BPnode::getPosInFile()
{
	return posInFile;
}

void BPnode::setPosInFile(int pos)
{
	posInFile = pos;
}

bool BPnode::HasKey(int key)
{
	for (int i = 0; i < keys.size(); ++i)
	{
		if (keys[i] == key) return true;
		if (keys[i] > key) return false;
	}
	return false;
}

bool BPnode::isOverFlow()
{
	if (num > NODE_MAX) return true;
	else return false;
}


int BPnode::searchKey(int key)
{
	int i = 0;
	for (i; i < keys.size(); ++i)
	{
		if (keys[i] >= key) break;
	}
	return i;
}

void BPnode::setState(int s)
{
	if (s == INNER_NODE) isLeaf = FALSE;
	if (s == LEAF) isLeaf = TRUE;
}

void BPnode::setNum(int n)
{
	num = n;
}

int BPnode::getNum()
{
	return num;
}

int BPnode::getState()
{
	return isLeaf;
}

void BPnode::insert(int key, int vpos, int length,int cpos)
{
	if (num == 0)
	{
		++num;
		keys.push_back(key);
		value.push_back(dataToken(vpos, length));
		deleted.push_back('y');
		children.push_back(cpos);
		children.push_back(cpos);
		return;
	}
	else 
	{
		int pos = searchKey(key);
		++num;
		keys.insert(keys.begin() + pos, key);
		deleted.insert(deleted.begin() + pos, 'y');
		value.insert(value.begin() + pos, dataToken(vpos, length));
		children.insert(children.begin() + pos + 1, cpos);
		return;
	}
}

void BPnode::remove(int key)
{
	int pos = searchKey(key);
	--num;
	keys.erase(keys.begin() + pos);
	value.erase(value.begin() + pos);
	if (pos == 0)
	{
		children.erase(children.begin());
	}
	else
	{
		children.erase(children.begin() + pos + 1);
	}
}


void BPnode::cancelDelete(int key, int vpos, int length)
{
	int i = searchKey(key);
	deleted[i] = 'y';
	value[i] = dataToken(vpos, length);
}


void BPnode::deleteKey(int key)
{
	int i = searchKey(key);
	deleted[i] = 'n';
}