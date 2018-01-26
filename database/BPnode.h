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

/*B+���ڵ��ļ�
���ڴ���ڵ���Ϣ*/

enum file { READ_ONLY,CREATE,READ_AND_WRITE };  //���ļ���ʽ
enum state{ INNER_NODE, LEAF};  //�ڵ�״̬
using namespace std;


class BPnode
{
protected:
	int posInFile = -1;
	int num = 0;
	int isLeaf = 1;
public:	
	vector<int> keys;            //��ֵ
	vector<dataToken> value;     //������Ϣ
	vector<int> children;        //�ӽڵ�λ��
	vector<char> deleted = vector<char>(NODE_MAX, 'y');  //��ֵ״̬
	BPnode() {};
	int getPosInFile();         //�õ��ڵ����ļ��е�λ��
	void setPosInFile(int pos); //���ýڵ����ļ��е�λ��
	bool HasKey(int key);       //��ѯ�Ƿ���ڼ�ֵkey�������Ƿ�ɼ���
	bool isOverFlow();          //�ж��Ƿ�����
	int searchKey(int key);     //����key(Ӧ�����ڣ���λ��
	void insert(int key, int vpos, int length,int cpos = 0);  //����һ��ֵ
	void remove(int key);       //ɾ����ֵkey����Ӧ��Ϣ���������紦��
	int getState();             //�õ��ڵ�״̬��Ҷ�ڵ�or�ڲ��ڵ㣩
	void setState(int s);       //���ýڵ�״̬
	void setNum(int n);         //���ü�ֵ��
	int getNum();               //��ȡ��ֵ��
	void deleteKey(int key);    //��key����Ϊ���ɼ�״̬������ɾ������
	void cancelDelete(int key,int vpos,int length);   //��key��Ϊ�ɼ�״̬
};
#endif

