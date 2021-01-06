#include "DistrictArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

DistrictArr::DistrictArr(int size)
{
	district_arr = new DistrictPtr[size];
	log_size = 0;
	real_size = size;
}

DistrictArr::DistrictArr(istream& in) { //load
	in.read(rcastc(&log_size), sizeof(log_size));
	real_size = log_size + 1;
	district_arr = new DistrictPtr[real_size];
	DistrictType type;
	for (int i = 0; i < log_size; i++)
	{
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
		case DistrictType::WTA:
			district_arr[i] = new WTADistrict(in);
			break;
		case DistrictType::RELATIVE:
			district_arr[i] = new RelativeDistrict(in);
			break;
		}
	}
}


DistrictArr::~DistrictArr()
{
	delete[] district_arr;
}

int DistrictArr::getLogSize() const
{
	return log_size;
}

const District& DistrictArr::getDistrict(int district_num) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (district_arr[i]->getId() == district_num) {
			return *district_arr[i];
		}
	}
	throw invalid_argument("No District with this ID");
}

District* DistrictArr::addDistrict(myString& name, int district_id, int electors, DistrictType type)// pay attention: when you create the new arr, you are creating a new DistrictPtr* and NOT DistritctArr.
//so 1) dont delete existing arr, just its DistrictPtr* and 2) reassing just the DistrictPtr*
{
	District* new_district = nullptr;
	if (log_size == real_size) {
		doubleSize();
	}
	if (type == WTA) {
		new_district = new WTADistrict(name, district_id, electors);

	}
	if (type == RELATIVE) {
		new_district = new RelativeDistrict(name, district_id, electors);
	}
	
	district_arr[log_size].setPtr(new_district);
	log_size++;
	return new_district;
}

int DistrictArr::addCitizen(myString& name, int id, int birthyear, int district_id)
{
	for (int j = 0; j < log_size; j++)//Validates
	{
		if (district_arr[j]->getCitizenArr().verifyId(id) == 100)
			return 100; //Citizen already exists!
	}

	for (int i = 0; i < log_size; i++)
	{
		if (district_arr[i]->getId() == district_id) {
			return district_arr[i]->addCitizen(name, id, birthyear);
		}
	}
	return 400; //No District with this id!
}

void DistrictArr::addParty(const Party* partynum)
{
	for (int i = 0; i < log_size; i++) {
		district_arr[i]->addParty(partynum);
	}
}

int DistrictArr::addVote(int party_num, int id)
{
	int vote_status;
	for (int i = 0; i < log_size; i++)
	{
		vote_status = district_arr[i]->addVote(party_num, id);
		if (vote_status == 200)
			return 200;
		if (vote_status == 100) //already voted!
			return 100;
	}
	return 400; //No citizen with this id!
}

int DistrictArr::addRep(int party_num, int id, int district_id)
{
	return district_arr[district_id]->addRep(party_num);
}

void DistrictArr::changeSize(int size)
{
	real_size = size;
	DistrictPtr* new_size = new DistrictPtr[real_size];
	memcpy(new_size, district_arr, sizeof(DistrictPtr) * log_size);
	for (int i = 0; i < log_size; i++)
	{
		district_arr[i].setPtr(nullptr);
	}
	delete[] district_arr;
	district_arr = new_size;
}

void DistrictArr::saveDistricts(ostream& out)const
{
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (int i = 0; i < log_size; ++i) {

		district_arr[i]->save(out);
	}
}

void DistrictArr::saveVotes(ostream& out)const
{
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (int i = 0; i < log_size; ++i) {
		district_arr[i]->saveVotes(out);
	}
}

void DistrictArr::load(istream& in)
{
	int loaded_size;
	in.read(rcastc(&loaded_size), sizeof(loaded_size));
	real_size = loaded_size + 1;
	changeSize(real_size);
	log_size = loaded_size;
	DistrictType type;
	for (int i = 0; i < log_size; i++)
	{
		district_arr[i].deleteDistrict(); // overun the old district
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
		case DistrictType::WTA:
			district_arr[i].setPtr(new WTADistrict(in));
			break;
		case DistrictType::RELATIVE:
			district_arr[i].setPtr(new RelativeDistrict(in));
			break;
		}
	}
}

void DistrictArr::link(istream& in, const PartyArr& party_map)
{
	int votes_arr_size;
	in.read(rcastc(&votes_arr_size), sizeof(votes_arr_size));
	for (int i = 0; i < votes_arr_size; ++i) {
		district_arr[i]->link(in, party_map);
	}
}

const Citizen* DistrictArr::getCitizen(int id, int district_num)const
{
	if (district_num != -1) {
		for (int i = 0; i < log_size; i++)
		{
			if (district_arr[i]->getId() == district_num) {
				return district_arr[i]->getCitizen(id);
			}
		}
		throw invalid_argument("No District with this ID");
	}
	const Citizen* get = nullptr;
	for (int i = 0; i < log_size; i++) {
		try {
			get = district_arr[i]->getCitizen(id);
			return get;
		}
		catch (std::exception& ex) {

		}
	}
	throw invalid_argument("No citizen with this ID");
}

ostream& operator<<(ostream& os, const DistrictArr& arr)
{
	for (int i = 0; i < arr.getLogSize(); i++)// moving in DistArr
	{
		for (int j = 0; j < arr[i].getCitizenArr().getLogSize(); j++)//in citizenArr
		{
			os << arr[i].getCitizenArr()[j] << endl
				<< "***********************************" << endl;
		}
	}
	return os;
}

void DistrictArr::printDistricts() const
{
	for (int i = 0; i < log_size; i++)
	{
		cout << *district_arr[i] << endl;
	}
}

void DistrictArr::doubleSize() //double real- size
{
	changeSize(real_size * 2);
}
