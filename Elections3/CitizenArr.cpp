#include "CitizenArr.h"
#include <iostream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
class District;
CitizenArr::CitizenArr(int size)
{
	try{
		citizen_map = {};
	}
	catch (bad_alloc& ex){
		throw;
	}
}

CitizenArr::CitizenArr(istream& in, District* dist) //load
{
	try{
		int log_size;
		in.read(rcastc(&log_size), sizeof(log_size));
		citizen_map = {};
		for (int i = 0; i < log_size; i++)
		{
			Citizen* new_citizen= new Citizen(in, dist);
			citizen_map.insert(pair<int, Citizen*>(new_citizen->getID(), new_citizen));
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
	citizen_map.clear();
}


void CitizenArr::addCitizenToArr(string& _name, int _id, int _birth_year, District* district)
{
	try {
		Citizen* new_citizen = new Citizen(_name, _id, _birth_year, district);
		citizen_map.insert(pair<int, Citizen*>(_id, new_citizen));
	}
	catch (bad_alloc& ex) {
		throw;
	}
}


void CitizenArr::addCitizenToArr(Citizen* person)
{
	if (citizen_map.find(person->getID()) != citizen_map.end())
		throw invalid_argument("This citizen already exists");// this citizen already exists
	citizen_map.insert(pair<int,Citizen*>(person->getID(), person));
}


void CitizenArr::verifyId(int id) const 
{
	if (citizen_map.find(id) != citizen_map.end())
		return;// This citizen exists- no problem
	else
		throw invalid_argument("Could not find a citizen with this ID");
}


const CitizenArr& CitizenArr::operator=(const CitizenArr origin) //Asked although its not in use. 
{
	if (citizen_map.size() > 0)
		citizen_map.clear();
	for (auto elem : origin.citizen_map)
	{
		int id = elem.first;
		citizen_map.insert(pair<int, Citizen*>(id, elem.second));
	}
	return *this;
}

void CitizenArr::save(ostream& out) const
{
	try {
		out.write(rcastcc(citizen_map.size()), sizeof(int));
		map<int, Citizen*>::iterator it;
		for (auto elem : citizen_map)
		{
			elem.second->save(out);
		}
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/writing/closing file");
	}
}

void CitizenArr::load(istream& in, District* dist)
{
	try {
		citizen_map.clear();
		int citizen_map_size;
		in.read(rcastc(&citizen_map_size), sizeof(int));
		for (int i=0; i< citizen_map_size; i++)
		{
			try {
				Citizen* citizen = new Citizen(in, dist);
				citizen_map.insert(pair<int, Citizen*>(citizen->getID(), citizen));
			}
			catch (bad_alloc& ex) {
				throw;
			}
		}
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}
