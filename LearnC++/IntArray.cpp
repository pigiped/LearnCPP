#include <stdio.h>
#include <stdlib.h> //per malloc
#include <string.h> //per memcpy
#include "IntArray.h"

static int dummy = 0;

IntArray::IntArray(int n)
{
	printf("alloc of %p\n", this);
	size = n;
	data = (int*)malloc(sizeof(int)*n);
}

IntArray::IntArray(const IntArray& arr)
{
	data = nullptr;
	//using the = operator override
	*this = arr;
}

void IntArray::operator=(const IntArray& arr)
{
	if (data)
		free(data);

	size = arr.size;
	data = (int*)malloc(sizeof(int) * size);

	printf("assignment op from %p to %p\n", &arr, this);

	memcpy(data, arr.data, sizeof(int) * size);
}

void IntArray::operator=(int i)
{
	IntArray tmp(1);
	tmp.set(0,i);
	*this = tmp;
}

IntArray IntArray::operator+(const IntArray& arr)
{
	IntArray ret(size + arr.size);

	memcpy(ret.data, data, sizeof(int) * size);
	memcpy(ret.data + size, arr.data, sizeof(int) * arr.size);

	return ret;
}

int& IntArray::operator[](int i)
{
	if (!safetyCheck(i))
		return dummy;
	return data[i];
}

IntArray::~IntArray()
{
	printf("dealloc of %p\n", this);
	free(data);
}

int IntArray::get(int index)
{
	if (!safetyCheck(index))
		return 0;
	return data[index];
}

void IntArray::set(int index, int value)
{
	if (safetyCheck(index)) 
	{
		data[index] = value;
	}
}

bool IntArray::safetyCheck(int index)
{
	return (index >= 0 && index < size);
}
