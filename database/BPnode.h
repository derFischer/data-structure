#ifndef BPNODE_H
#define BPNODE_H
#include<iostream>
#include<vector>
#include<fstream>
#include<set>
#include"space.h"
#define NODE_MIN  9
#define NODE_MAX  16
#define INDEX_MAX ( NODE_MAX * 4 + 3) * 4 + 1 + NODE_MAX
#define EXIST 1
#define DELETE 2

/*B+树节点文件
用于处理节点信息*/

enum file { READ_ONLY,CREATE,READ_AND_WRITE };  //打开文件方式
enum state{ INNER_NODE, LEAF};  //节点状态
using namespace std;


class BPnode
{
protected:
	int posInFile = -1;
	int num = 0;
	int isLeaf = 1;
public:	
	vector<int> keys;            //键值
	vector<dataToken> value;     //数据信息
	vector<int> children;        //子节点位置
	vector<char> deleted = vector<char>(NODE_MAX, 'y');  //键值状态
	BPnode() {};
	int getPosInFile();         //得到节点在文件中的位置
	void setPosInFile(int pos); //设置节点在文件中的位置
	bool HasKey(int key);       //查询是否存在键值key（无论是否可见）
	bool isOverFlow();          //判断是否上溢
	int searchKey(int key);     //返回key(应该所在）的位置
	void insert(int key, int vpos, int length,int cpos = 0);  //插入一对值
	void remove(int key);       //删除键值key及对应信息，用于上溢处理
	int getState();             //得到节点状态（叶节点or内部节点）
	void setState(int s);       //设置节点状态
	void setNum(int n);         //设置键值数
	int getNum();               //获取键值数
	void deleteKey(int key);    //将key的设为不可见状态，用于删除处理
	void cancelDelete(int key,int vpos,int length);   //将key设为可见状态
};
#endif

