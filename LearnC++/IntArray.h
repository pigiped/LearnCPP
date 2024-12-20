#pragma once
class IntArray
{
public:
	IntArray(int n);				//constructor
	IntArray(const IntArray& arr);	//copy constructor
	~IntArray();					//destructor

	int get(int index);
	void set(int index, int value);

	void operator=(const IntArray& arr);
	void operator=(int i);

	//concat
	IntArray operator+(const IntArray& arr);

private:
	size_t size;
	int* data;

	bool safetyCheck(int index);
};

