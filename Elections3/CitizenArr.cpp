#include "CitizenArr.h"
#include <iostream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
class District;
CitizenArr::CitizenArr(int size)
{
	log_size = 0;
	real_size = size;
	citizen_arr = new CitizenPtr[real_size];
}

CitizenArr::CitizenArr(istream& in, District* dist) //load
{
	in.read(rcastc(&log_size), sizeof(log_size));
	real_size = log_size + 1;
	citizen_arr = new CitizenPtr[real_size];
	for (int i = 0; i < log_size; i++)
	{
		citizen_arr[i] = new Citizen(in, dist);
	}
}

CitizenArr::~CitizenArr()
{
	delete[] citizen_arr;
}

int CitizenArr::getLogSize() const
{
	return(log_size);
}

Citizen* CitizenArr::getCitizenByID(const int id) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (citizen_arr[i]->getID() == id)
			return (citizen_arr[i].getAddress());
	}
	return nullptr;
}

void CitizenArr::doubleSize()
{
	changeSize(real_size * 2);
}

int CitizenArr::addCitizenToArr(myString& _name, int _id, int _birth_year,District* district)
{
	if (log_size == real_size)
		doubleSize();
	citizen_arr[log_size].setPtr(new Citizen(_name, _id, _birth_year, district));
	log_size++;
	return 200;//validates
}

int CitizenArr::addCitizenToArr(Citizen* person)
{
	for (int i = 0; i < log_size; i++)
	{
		if (citizen_arr[i]->getID() == person->getID())
			return 100;// this citizen already exists
	}
	if (log_size == real_size)
		doubleSize();
	citizen_arr[log_size].setPtr(person);
	log_size++;
	return 200;//validates
}

int CitizenArr::verifyId(int id) const //to check if voted already
{
	int i;
	for (i = 0; i < log_size; i++)
	{
		if (citizen_arr[i]->getID() == id) {
			;
			return 100;
		}
	}
	return 400;
}

const CitizenArr& CitizenArr::operator=(const CitizenArr origin) //Asked although its not in use. 
{
	if (citizen_arr != nullptr)
		delete[] citizen_arr;
	log_size = origin.log_size;
	real_size = origin.real_size;
	for (int i = 0; i < log_size; i++)
	{
		citizen_arr[i] = origin.citizen_arr[i];
	}
	return *this;
}

void CitizenArr::save(ostream& out) const
{
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (int i = 0; i < log_size; i++)
		citizen_arr[i]->save(out);
}

void CitizenArr::load(istream& in, District* dist)
{
	int citizen_arr_size;
	in.read(rcastc(&citizen_arr_size), sizeof(int));
	changeSize(citizen_arr_size);

	for (int i = 0; i < citizen_arr_size; i++)
	{
		citizen_arr[i].deleteCitizen();
		Citizen* citizen = new Citizen(in, dist);
		citizen_arr[i].setPtr(citizen);
	}
	log_size = citizen_arr_size;
}

void CitizenArr::changeSize(int size)
{
	real_size = size;
	CitizenPtr* tmp = new CitizenPtr[real_size];
	for (int i = 0; i < log_size; i++)
	{
		tmp[i] = citizen_arr[i];
		citizen_arr[i].setPtr(nullptr);
	}

	delete[] citizen_arr;// free the old arr
	citizen_arr = tmp;
}
