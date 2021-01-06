#include "myString.h"
#include <iostream>
using namespace std;


#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

myString::myString(const char* _str) {
	int i = 0;
	while (_str[i] != '\0') {
		i++;
	}
	str = new char[i];
	size = i + 1;
	i = 0;
	while (_str[i] != '\0') {
		str[i] = _str[i];
		i++;
	}
}

myString::myString(const myString& _str)
{
	int i = 0;
	while (_str[i] != '\0' && _str[i] != -3) {
		i++;
	}
	str = new char[i + 1];
	size = i + 1;
	i = 0;
	for (int i = 0; i < size; i++)
	{
		str[i] = _str[i];
	}
	str[size - 1] = '\0';
}

myString::myString()
{
	size = 0;
	str = nullptr;
}

myString::~myString()
{
	delete[] str;
}

bool myString::operator==(const char* origin)
{
	for (int i = 0; i < size; i++)
	{
		if (str[i] != origin[i])
			return false;
	}
	return true;
}

myString& myString::operator=(const char* origin)
{
	if (str != nullptr)
		delete[]str;
	int i = 0;
	while (origin[i] != '\0' && origin[i] != -3) {
		i++;
	}
	str = new char[i + 1];
	size = i + 1;
	i = 0;
	for (int i = 0; i < size; i++)
	{
		str[i] = origin[i];
	}
	str[size - 1] = '\0';
	return *this;
}

myString& myString::operator=(const myString origin)
{
	if (str != nullptr)
		delete[]str;
	size = origin.size;
	str = new char[size];
	for (int i = 0; i < size; i++)
	{
		str[i] = origin.str[i];
	}
	return *this;
}

myString& myString::operator+(const myString add)
{
	int new_size = size + add.size - 1;
	char* result = new char[new_size];
	int index = 0;
	for (int i = 0; i < size - 1; i++)
	{
		result[index] = str[i];
		index++;
	}
	for (int i = 0; i < add.size - 1; i++)
	{
		result[index] = add.str[i];
		index++;
	}
	result[index] = '\0';
	delete str;
	size = new_size;
	str = result;
	return *this;
}


int myString::getSize()
{
	return size;
}

void myString::reverse()
{
	char* reversed = new char[size];
	int i = 0;
	for (int i = 0; i < size; i++)
	{
		reversed[i] = str[size - 2 - i];
	}
	reversed[size - 1] = '\0';
	delete str;
	str = reversed;
}

void myString::save(ostream& out) const
{
	out.write(rcastcc(&size), sizeof(size));
	out.write(rcastcc(str), size);

}

void myString::load(istream& in)
{
	if (str != nullptr)
		delete[]str;
	in.read(rcastc(&size), sizeof(size));
	str = new char[size];
	in.read(rcastc(str), size);
}
void myString::ignore(istream& in) {
	int size_ignore;
	in.read(rcastc(&size_ignore), sizeof(size_ignore));
	in.ignore(size_ignore);
}




myString itos(int num)
{

	char num_char[256]{ '\0' };
	int i = 0;
	while (num != 0) {
		num_char[i] = num % 10 + 48;
		num /= 10;
		i++;
	}
	myString str(num_char);
	str.reverse();
	return str;
}

ostream& operator<<(ostream& os, const myString& str)
{
	os << str.str;
	return os;
}

istream& operator>>(istream& is, myString& str)
{
	str.size = 100;
	int log_size = 0;
	char buffer[256];
	is.getline(buffer, 256);
	str = buffer;
	return is;
}

void increaseSizeArr(char*& name, int realsize, int logsize)
{
	char* tmp = new char[realsize * 2];
	int i = 0;
	while (i <= logsize)
	{
		tmp[i] = name[i];
		i++;
	}
	delete[] name;
	name = tmp;
}
