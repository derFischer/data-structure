#ifndef CACHE_H
#define CACHE_H
#include "link.h"

class cacheRec
{
private:
	link recent;
public:
	cacheRec() {};
	void addRecord(int key, string value);
	void deleteRecord(int key);
	bool ifHasKey(int key);
	string getValue(int key);
};

void cacheRec::addRecord(int key, string value)
{
	recent.insert(key, value);
}

void cacheRec::deleteRecord(int key)
{
	recent.remove(key);
}

bool cacheRec::ifHasKey(int key)
{
	return recent.ifHasKey(key);
}

string cacheRec::getValue(int key)
{
	return recent.searchKey(key)->value;
}
#endif
