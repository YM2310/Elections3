#pragma once
#include <iostream>
using namespace std;

class myString {
public:
	myString(const char* _str);
	myString(const myString& _str);
	myString();
	~myString();
	int getSize();
	void reverse();
	void save(ostream& out) const;
	void load(istream& in);
	void static ignore(istream& in);


	friend ostream& operator<<(ostream& os, const myString& str);
	friend istream& operator>>(istream& os, myString& str);
	bool operator==(const char* origin);
	myString& operator=(const char* origin);
	myString& operator=(const myString origin);
	myString& operator+(const myString add);
	char& operator[](int i) { return str[i]; }
	const char& operator[](int i) const { return str[i]; }
	
private:
	char* str;
	int size;
};
myString itos(int num);