#ifndef DATAFILE_H
#define DATAFILE_H
#include<iostream>
#include<fstream>
#include<string>
#include "buffer.h"
#include "BPnode.h"
#include "space.h"

using namespace std;

class wrongDataFile{};
class datafile
{
private:
	fstream f;
	databin freeSpace;
public:
	datafile() {};
	void openDatafile(string path, file method);
	void closeDatafile();
	string valueData(int pos,int length);
	int insert(string value);
	void deleteValue(int pos, int length);
	int modify(int pos, int length, string value);
};

#endif
