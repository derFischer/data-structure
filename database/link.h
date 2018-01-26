#ifndef LINK_H
#define LINK_H
#include<iostream>
#include<string>
#define LINK_MAX 10
using namespace std;

struct node
{
	int key;
	string value;
	node *pre = NULL;
	node *next = NULL;
	node(int key, string value)
	{
		this->key = key;
		this->value = value;
	}
};

class link
{
private:
	node *start = NULL;
	node *end = NULL;
	int size = 0;
public:
	link() {};
	bool ifFull();
	bool ifEmpty();
	node* searchKey(int key);
	bool ifHasKey(int key);
	int getSize();
	void insert(int key, string value);
	void remove(int key);
	~link()
	{
		if (size == 0)return;
		if (size == 1)
		{
			delete start;
			return;
		}
		else
		{
			node *tmp = start;
			while (tmp != NULL)
			{
				node *t = tmp;
				tmp = t->next;
				delete t;
			}
			return;
		}
	}
};


#endif
