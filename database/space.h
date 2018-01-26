#ifndef SPACE_H
#define SPACE_H
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct dataToken
{
	int pos;
	int length;
	dataToken(int pos = 0,int length = 0) 
	{
		this->pos = pos;
		this->length = length;
	};
	bool operator < (const dataToken &obj)
	{
		return this->length < obj.length;
	}
};


class databin
{
private:
	vector<dataToken> dataspace;
	int size = 0;
public:
	databin() {};
	void insert(int offset, int length);
	void sortVector();
	int getPos(int datasize);
};


#endif
