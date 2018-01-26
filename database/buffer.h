#ifndef BUFFER_H
#define BUFFER_H
#include<iostream>
#include<queue>
#include<fstream>
#define BUFFER_MAX 10
using namespace std;

/*only used to reserve modified message*/
struct dataTokenBuffer
{
	int pos;
	string value;
	dataTokenBuffer(int pos, string value = "")
	{
		this->pos = pos;
		this->value = value;
	}
};

#endif
