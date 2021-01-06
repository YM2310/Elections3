#pragma once
#include "CitizenPtr.h"

class CitizenArr
{
public:
	CitizenArr( int size = 1); 
	CitizenArr(istream& in, District* dist);//for loading
	CitizenArr(const CitizenArr&) = delete;
	~CitizenArr();

	/*Getters*/
	int getLogSize() const;
	Citizen* getCitizenByID(const int id) const;
	int verifyId(int id) const;// returnes if there's a citizen with this id within the arr, and if he voted

	/*Adders*/
	int addCitizenToArr(myString& _name, int _id, int _birth_year, District* district);// will call ctor citizen, logsize++, if () realsize - increasesize
	int addCitizenToArr(Citizen* person);


	/*Operators*/
	const Citizen& operator[](int i)const { return *citizen_arr[i]; } //returns the actual citizen, good for printing
	const CitizenArr& operator=(const CitizenArr origin);
	void save(ostream& out) const;
	void load(istream& in, District* dist);
private:
	void changeSize(int size); 
	void doubleSize();
	CitizenPtr* citizen_arr;
	int log_size;
	int real_size;
};
