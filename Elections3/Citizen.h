#pragma once
#include <iostream>
#include <string>
using namespace std;
class District;
class Citizen
{
public:
	Citizen(string& _name, int _id, int _birth_year, District* _district, bool _voted = false);
	Citizen(istream& in, District* dist);
	Citizen();
	~Citizen();

	/*Getters: */
	bool getIfVoted() const;
	int getBirthYear() const;
	int getID() const;
	const string& getName() const;

	/*Setters:*/
	bool setIfVoted(bool const ifVoted);

	/*Operators*/
	friend ostream& operator<<(ostream& os, const Citizen& dt);

	/*Files: */
	void save(ostream& out) const;

private:
	const District* district;
	string name;
	int id;
	int birth_year;
	bool voted;
};
