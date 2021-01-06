#include "Reps.h"
#include "DistrictArr.h"

Reps::Reps(int size, const District* _district_num)
{
	distrtict_num = _district_num;
	log_size = 0;
	real_size = size;
	citizen_arr = new const Citizen * [real_size];
}

Reps::~Reps()
{
	for (int i = 0; i < real_size; i++)
	{
		citizen_arr[i] = nullptr;
	}
	delete[] citizen_arr;
}

int Reps::getLogSize() const
{
	return log_size;
}

int Reps::getDistrictNum() const
{
	return distrtict_num->getId();
}

const District* Reps::getDistrict() const
{
	return distrtict_num;
}

void Reps::doubleSize()
{
	real_size *= 2;
	const Citizen** new_size = new const Citizen * [real_size];
	memcpy(new_size, citizen_arr, sizeof(Citizen*) * log_size);
	delete citizen_arr;
	citizen_arr = new_size;
}

void Reps::changeSize(int new_size)
{
	real_size = new_size;
	const Citizen** new_arr = new const Citizen * [real_size];
	memcpy(new_arr, citizen_arr, sizeof(Citizen*) * log_size);
	delete citizen_arr;
	citizen_arr = new_arr;
}


int Reps::addCitizenToArr(const Citizen* person)
{
	if (log_size == real_size) {
		doubleSize();
	}
	citizen_arr[log_size] = person;
	log_size++;
	return 200;//validates
}

myString Reps::getNameOfRep(int idx) const
{
	return citizen_arr[idx]->getName();
}

int Reps::getIDRep(int idx) const
{
	return citizen_arr[idx]->getID();
}


void Reps::setDistrict(const District* district)
{
	this->distrtict_num = district;
}

void Reps::save(ostream& out) const
{
	int  reps_size, district, citizen;
	district = distrtict_num->getId();
	out.write(rcastcc(&district), sizeof(int));
	out.write(rcastcc(&log_size), sizeof(int));
	for (int i = 0; i < log_size; i++)
	{
		citizen = citizen_arr[i]->getID();
		out.write(rcastcc(&citizen), sizeof(int));
	}

}

void Reps::load(istream& in, const DistrictArr& district_map)
{
	int  reps_size,district, citizen;
	in.read(rcastc(&district), sizeof(int));
	distrtict_num = &district_map.getDistrict(district);
	in.read(rcastc(&reps_size), sizeof(int));
	changeSize(reps_size);
	log_size = reps_size;
	for (int i = 0; i < reps_size; i++)
	{
		in.read(rcastc(&citizen), sizeof(int));
		citizen_arr[i] = district_map.getCitizen(citizen);
	}
}

Reps& Reps::operator=(const Reps& origin)
{
	distrtict_num = origin.distrtict_num;
	log_size = origin.log_size;
	real_size = origin.real_size;
	for (int i = 0; i < log_size; i++)
	{
		citizen_arr[i] = origin.citizen_arr[i];
	}
	return *this;
}
