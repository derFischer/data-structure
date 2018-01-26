#include "link.h"

bool link::ifFull()
{
	if (size >= LINK_MAX) return true;
	else return false;
}

bool link::ifEmpty()
{
	if (size == 0) return true;
	else return false;
}

node* link::searchKey(int key)
{
	node *tmp = start;
	if (tmp == NULL) return NULL;
	for (int i = 0; i < size; ++i)
	{
		if (tmp == NULL) break;
		if (tmp->key == key) return tmp;
		else
		{
			tmp = tmp->next;
		}
	}
	return NULL;
}

bool link::ifHasKey(int key)
{
	return (!(searchKey(key) == NULL));
}
int link::getSize()
{
	return size;
}

void link::insert(int key, string value)
{
	if (ifEmpty())
	{
		node *s = new node(key, value);
		start = s;
		++size;
		return;
	}
	else
	{
		if (ifFull())
		{
			--size;
			node *tmp = end;
			end = tmp->pre;
			delete tmp;
			end->next = NULL;
		}
		node *tmp = new node(key, value);
		start->pre = tmp;
		tmp->next = start;
		++size;
		if (getSize() == 2) end = start;
		start = tmp;
		return;
	}
}

void link::remove(int key)
{
	node *tmp = searchKey(key);
	if (tmp != NULL)
	{
		if (tmp == start)
		{
			if (getSize() == 1)
			{
				delete start;
				start = NULL;
				--size;
				return;
			}
			if (getSize() == 2)
			{
				delete start;
				start = end;
				start->pre = NULL;
				end = NULL;
				--size;
				return;
			}
			else
			{
				start = start->next;
				start->pre = NULL;
				delete tmp;
				--size;
				return;
			}
		}
		if (tmp == end)
		{
			if (getSize() == 2)
			{
				delete end;
				end = NULL;
				start->next = NULL;
				--size;
				return;
			}
			else
			{
				end = end->pre;
				end->next = NULL;
				delete tmp;
				--size;
				return;
			}
		}
		else
		{
			tmp->pre->next = tmp->next;
			tmp->next->pre = tmp->pre;
			delete tmp;
			--size;
			return;
		}
	}
}
