#include "myString.h"
#include "Citizen.h"
#include "District.h"
#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 

Citizen::Citizen(myString& _name, int _id, int _birth_year, District* _district, bool _voted)
{
	district = _district;
	name = _name;
	id = _id;
	birth_year = _birth_year;
	voted = _voted;
}


Citizen::Citizen()
{
	district = nullptr;
	name = "";
	id = -1;
	birth_year = -1;
	voted = false;
}

Citizen::Citizen(istream& in, District* dist) //load
{
	this->district = dist;
	name.load(in);
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&birth_year), sizeof(birth_year));
	in.read(rcastc(&voted), sizeof(voted));
}

Citizen::~Citizen()
{
}

bool Citizen::getIfVoted() const
{
	return(voted);
}

int Citizen::getBirthYear() const
{
	return(birth_year);
}

int Citizen::getID() const
{
	return(id);
}
const myString& Citizen::getName() const
{
	return(name);
}

bool Citizen::setIfVoted(bool const ifVoted)
{
	voted = ifVoted;
	return true;
}

ostream& operator<<(ostream& os, const Citizen& citizen) // to print citizen
{
	os << "***********************************" << endl <<
		"Name: " << citizen.name << endl <<
		"Id:" << citizen.id << endl <<
		"Birth Year: " << citizen.birth_year << endl <<
		"District: " << citizen.district->getName();

	return os;
}

void Citizen::save(ostream& out) const
{
	name.save(out);
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&birth_year), sizeof(birth_year));
	out.write(rcastcc(&voted), sizeof(voted));
}
