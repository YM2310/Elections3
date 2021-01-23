#include "Reps.h"
#include "DistrictArr.h"

Reps::Reps(int size, const District* _district_num) :citizen_arr(size)
{
	distrtict_num = _district_num;

}

Reps::~Reps()
{

	for (auto& citizen : citizen_arr) {
		citizen = nullptr;
	}
}

int Reps::getLogSize() const
{
	return citizen_arr.size();
}

int Reps::getDistrictNum() const
{
	return distrtict_num->getId();
}

const District* Reps::getDistrict() const
{
	return distrtict_num;
}


void Reps::addCitizenToArr(const Citizen* person)
{
	try {
		citizen_arr.push_back(person);
	}
	catch (...) {
		throw;
	}
}

string Reps::getNameOfRep(int idx) const
{
	try {
		return citizen_arr[idx]->getName();
	}
	catch (...) {
		throw;
	}
}

int Reps::getIDRep(int idx) const//// add checks!
{
	try {
		return citizen_arr[idx]->getID();
	}
	catch (...) {
		throw;
	}
}


void Reps::setDistrict(const District* district)
{
	this->distrtict_num = district;
}

void Reps::save(ostream& out) const
{
	try {
		int  reps_size, district, citizen, log_size = citizen_arr.size();
		district = distrtict_num->getId();
		out.write(rcastcc(&district), sizeof(int));
		out.write(rcastcc(&log_size), sizeof(int));
		for (int i = 0; i < log_size; i++)
		{
			citizen = citizen_arr[i]->getID();
			out.write(rcastcc(&citizen), sizeof(int));
		}
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
	if (out.good() == false) {
		throw runtime_error("file not good!");
	}


}

void Reps::load(istream& in, const DistrictArr& district_map)
{
	try {
		int  reps_size, district, citizen;
		in.read(rcastc(&district), sizeof(int));
		distrtict_num = &district_map.getDistrict(district);
		in.read(rcastc(&reps_size), sizeof(int));
		for (int i = 0; i < reps_size; i++)
		{
			in.read(rcastc(&citizen), sizeof(int));
			citizen_arr.push_back(district_map.getCitizen(citizen));
		}
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

Reps& Reps::operator=(const Reps& origin)
{
	distrtict_num = origin.distrtict_num;
	citizen_arr.clear();
	for (int i = 0; i < origin.citizen_arr.size(); i++)
	{
		citizen_arr.push_back(origin.citizen_arr[i]);
	}
	return *this;
}
