#include "Citizen.h"
#include "District.h"
#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 

Citizen::Citizen(string& _name, int _id, int _birth_year, District* _district, bool _voted)
{
	if (_id > 999999999 || _id < 100000000) //checkes if ID is not 9 digits
		throw invalid_argument("Invalid Citizen ID");
	//if- age is less than 18- checks from election
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
	try {
		this->district = dist;
		in.read(rcastc(&name), sizeof(name));
		in.read(rcastc(&id), sizeof(id));
		in.read(rcastc(&birth_year), sizeof(birth_year));
		in.read(rcastc(&voted), sizeof(voted));
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
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
const string& Citizen::getName() const
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
	try {
		out.write(rcastcc(&name), sizeof(name));
		out.write(rcastcc(&id), sizeof(id));
		out.write(rcastcc(&birth_year), sizeof(birth_year));
		out.write(rcastcc(&voted), sizeof(voted));
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/writing/closing file");
	}
}
