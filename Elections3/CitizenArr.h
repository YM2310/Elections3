#pragma once
#include "CitizenPtr.h"
#include <map>

class CitizenArr
{
public:
	CitizenArr(int size = 1);
	CitizenArr(istream& in, District* dist);//for loading
	CitizenArr(const CitizenArr&) = delete;
	~CitizenArr();

	/*Getters*/
	void verifyId(int id) const;// returnes if there's a citizen with this id within the arr, and if he voted

	/*Adders*/
	void addCitizenToArr(string& _name, int _id, int _birth_year, District* district);// will call ctor citizen, logsize++, if () realsize - increasesize
	void addCitizenToArr(Citizen* person);


	/*Operators*/
	const CitizenArr& operator=(const CitizenArr origin);
	void save(ostream& out) const;
	void load(istream& in, District* dist);

	//STL://
	map <int, Citizen*> citizen_map; //int= id of citizen
};
