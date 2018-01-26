#include "space.h"

void databin::insert(int offset, int length)
{
	dataspace.push_back(dataToken(offset, length));
	++size;
}

void databin::sortVector()
{
	sort(dataspace.begin(), dataspace.end());
}

int databin::getPos(int datasize)
{
	if (size == 0) return -1;
	else
	{
		int pos;
		sortVector();
		if (dataspace[size - 1].length < datasize) return -1;
		else
		{
			pos = dataspace[size - 1].pos;
			if (dataspace[size - 1].length == datasize)
			{
				dataspace.pop_back();
				--size;
				return pos;
			}
			else
			{
				int newLength = dataspace[size - 1].length - datasize;
				int newPos = dataspace[size - 1].pos + datasize;
				dataspace.pop_back();
				dataspace.push_back(dataToken(newPos, newLength));
				return pos;
			}
		}
	}
	return -1;
}
