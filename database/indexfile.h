#ifndef INDEXFILE_H
#define INDEXFILE_H
#include "BPnode.h"
#include "space.h"
#include <memory>

class wrongIndexFile{};
class keyExist{};
class keyDExist{};
class indexfile
{
private:
	fstream f;
	vector<BPnode> reserve;
	int rootPos  = -1;
	bool empty = true;
	vector<BPnode> path;
public:
	indexfile() {};
	void openIndexfile(string path,file method);
	void closeIndexfile();
	void insert(int key, int vpos, int length, int cpos = 0, BPnode &obj = BPnode());
	void deleteIdx(int key,BPnode &obj);
	void overFlow(BPnode &obj);
	BPnode search(int key);     //从索引文件中获取key应该所在的叶节点（无论key是否存在）
	BPnode searchInsert(int key);  //在search的同时，将父节点都加入path中
	int writeBPnode(BPnode &obj);  //将节点写入索引文件
	BPnode getBPMessage(int pos);  //从索引文件获取节点
	void freshenIndexFile();     //统一刷新
	void writeRootPos();         //写入根节点位置
	bool isEmpty();              //索引文件是否空
	void setEmpty(int e);        //设置索引文件是否空
	bool key(int key,BPnode &tmp);   //索引文件中是否存在key
	void pathClear();                //清空path
	void recovery(int key, BPnode &obj);   //恢复
};
#endif
