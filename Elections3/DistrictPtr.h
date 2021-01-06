#pragma once
#include "District.h"
class DistrictPtr
{
public:
	DistrictPtr(District* p) : ptr(p) {};
	DistrictPtr();
	~DistrictPtr();

	void deleteDistrict();

	/*Setters: */
	void setPtr(District* citizen);

	/*Operators*/
	District* operator->() { return ptr; }
	District& operator*() { return *ptr; }

private:
	District* ptr;
};

