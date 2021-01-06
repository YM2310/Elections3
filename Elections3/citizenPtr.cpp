#include "citizenPtr.h"

CitizenPtr::CitizenPtr()
{
	ptr = nullptr;
}

CitizenPtr::~CitizenPtr()
{
	delete ptr;
}

CitizenPtr::CitizenPtr(myString _name, int _id, int _birth_year,District* _district, bool _voted)
{
	ptr = new Citizen(_name, _id, _birth_year,_district,_voted);
}

bool CitizenPtr::setPtr(Citizen* citizen)
{
	ptr = citizen;
	return true;
}

void CitizenPtr::deleteCitizen()
{
	delete ptr;
}

Citizen* CitizenPtr::getAddress()
{
	return ptr;
}

bool CitizenPtr::isNull()
{
	if (ptr == nullptr)
		return true;
	return false;
}
