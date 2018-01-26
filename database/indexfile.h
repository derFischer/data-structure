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
	BPnode search(int key);     //�������ļ��л�ȡkeyӦ�����ڵ�Ҷ�ڵ㣨����key�Ƿ���ڣ�
	BPnode searchInsert(int key);  //��search��ͬʱ�������ڵ㶼����path��
	int writeBPnode(BPnode &obj);  //���ڵ�д�������ļ�
	BPnode getBPMessage(int pos);  //�������ļ���ȡ�ڵ�
	void freshenIndexFile();     //ͳһˢ��
	void writeRootPos();         //д����ڵ�λ��
	bool isEmpty();              //�����ļ��Ƿ��
	void setEmpty(int e);        //���������ļ��Ƿ��
	bool key(int key,BPnode &tmp);   //�����ļ����Ƿ����key
	void pathClear();                //���path
	void recovery(int key, BPnode &obj);   //�ָ�
};
#endif
