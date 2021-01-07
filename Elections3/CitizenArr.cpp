#include "CitizenArr.h"
#include <iostream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
class District;
CitizenArr::CitizenArr(int size)
{
	log_size = 0;
	real_size = size;
	try{
		citizen_arr = new CitizenPtr[real_size];
	}
	catch (bad_alloc& ex){
		throw;
	}
}

CitizenArr::CitizenArr(istream& in, District* dist) //load
{
	try{
		in.read(rcastc(&log_size), sizeof(log_size));
		real_size = log_size + 1;
		citizen_arr = new CitizenPtr[real_size];
		for (int i = 0; i < log_size; i++)
		{
			citizen_arr[i] = new Citizen(in, dist);
		}
	}
	catch (bad_alloc& ex) {
		throw; 
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
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
	throw invalid_argument("No citizen with this id");
}

void CitizenArr::doubleSize()
{
	changeSize(real_size * 2);
}

void CitizenArr::addCitizenToArr(myString& _name, int _id, int _birth_year, District* district)
{
	if (log_size == real_size)
		doubleSize();
	try {
		citizen_arr[log_size].setPtr(new Citizen(_name, _id, _birth_year, district));
		log_size++;
	}
	catch (bad_alloc& ex) {
		throw;
	}
}

void CitizenArr::addCitizenToArr(Citizen* person)
{
	for (int i = 0; i < log_size; i++)
	{
		if (citizen_arr[i]->getID() == person->getID())
			throw invalid_argument("This citizen already exists");// this citizen already exists
	}
	if (log_size == real_size)
		doubleSize();
	citizen_arr[log_size].setPtr(person);
	log_size++;
}

void CitizenArr::verifyId(int id) const 
{
	int i;
	for (i = 0; i < log_size; i++)
	{
		if (citizen_arr[i]->getID() == id) {
			return;// This citizen exists- no problem
		}
	}
	if (i == log_size)
		throw invalid_argument("Could not find a citizen with this ID");
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
	try {
		out.write(rcastcc(&log_size), sizeof(log_size));
		for (int i = 0; i < log_size; i++)
			citizen_arr[i]->save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/writing/closing file");
	}
}

void CitizenArr::load(istream& in, District* dist)
{
	try {
		int citizen_arr_size;
		in.read(rcastc(&citizen_arr_size), sizeof(int));
		changeSize(citizen_arr_size);

		for (int i = 0; i < citizen_arr_size; i++)
		{
			try {
				citizen_arr[i].deleteCitizen();
				Citizen* citizen = new Citizen(in, dist);
				citizen_arr[i].setPtr(citizen);
			}
			catch (bad_alloc& ex) {
				throw;
			}
		}
		log_size = citizen_arr_size;
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void CitizenArr::changeSize(int size)
{
	try {
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
	
	catch (bad_alloc& ex) {
		throw;
	}
}
