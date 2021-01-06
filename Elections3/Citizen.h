#pragma once
#include <iostream>
#include "myString.h"
using namespace std;
class District;
class Citizen
{
public:
	Citizen(myString& _name, int _id, int _birth_year, District* _district, bool _voted = false);
	Citizen(istream& in, District* dist);
	Citizen();
	~Citizen();

	/*Getters: */
	bool getIfVoted() const;
	int getBirthYear() const;
	int getID() const;
	const myString& getName() const;

	/*Setters:*/
	bool setIfVoted(bool const ifVoted);

	/*Operators*/
	friend ostream& operator<<(ostream& os, const Citizen& dt);

	/*Files: */
	void save(ostream& out) const; 

private:
	const District* district;
	myString name;
	int id;
	int birth_year;
	bool voted;
};
