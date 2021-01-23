
#include "DistrictArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

DistrictArr::DistrictArr(int size) :
	district_map {}
{
}

DistrictArr::DistrictArr(istream& in) { //load
	int log_size;
	in.read(rcastc(&log_size), sizeof(log_size));
	district_map = {};
	DistrictType type;
	for (int i = 0; i < log_size; i++)
	{
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
		case DistrictType::WTA:
		{
			District* new_dist_WTA = new WTADistrict(in);
			district_map.insert(pair<int, District*>(new_dist_WTA->getId(), new_dist_WTA));
			break;
		}
		
		case DistrictType::RELATIVE:
		{
			District* new_dist_relative = new RelativeDistrict(in);
			district_map.insert(pair<int, District*>(new_dist_relative->getId(), new_dist_relative));
			break;
		}
			
		}

	}
}


DistrictArr::~DistrictArr()
{
	district_map.clear();
}

const District& DistrictArr::getDistrict(int district_num) const
{
	if(district_map.find(district_num) == district_map.end())
		throw invalid_argument("No District with this ID");
}

District* DistrictArr::addDistrict(string& name, int district_id, int electors, DistrictType type)// pay attention: when you create the new arr, you are creating a new DistrictPtr* and NOT DistritctArr.
//so 1) dont delete existing arr, just its DistrictPtr* and 2) reassing just the DistrictPtr*
{
	District* new_district = nullptr;
	if (type == WTA) {
		new_district = new WTADistrict(name, district_id, electors);

	}
	if (type == RELATIVE) {
		new_district = new RelativeDistrict(name, district_id, electors);
	}

	district_map.insert(pair<int, District*>(district_id, new_district));
	return new_district;
}

int DistrictArr::addCitizen(string& name, int id, int birthyear, int district_id)
{
	if (district_map.find(district_id) == district_map.end())
		return 400; //No District with this id! should be throw
	for (auto elem : district_map)//Validates
	{
		if (elem.second->getCitizenArr().citizen_map.find(id) != elem.second->getCitizenArr().citizen_map.end())
			return 100; //Citizen already exists!- Should be turned to throw!
	}
	district_map.find(district_id)->second->addCitizen(name, id, birthyear);
}

void DistrictArr::addParty(const Party* partynum)
{
	for (auto elem: district_map) {
		elem.second->addParty(partynum);
	}
}

int DistrictArr::addVote(int party_num, int id)
{
	int vote_status;
	for (auto elem : district_map)
	{
		vote_status = elem.second->addVote(party_num, id);
		if (vote_status == 200)
			return 200;
		if (vote_status == 100) //already voted!
			return 100;
	}
	return 400; //No citizen with this id!
}

int DistrictArr::addRep(int party_num, int id, int district_id)
{
	return district_map.find(district_id)->second->addRep(party_num);
}

void DistrictArr::saveDistricts(ostream& out)const
{
	out.write(rcastcc(district_map.size()), sizeof(int));
	for (auto elem: district_map) {
		elem.second->save(out);
	}
}

void DistrictArr::saveVotes(ostream& out)const
{
	out.write(rcastcc(district_map.size()), sizeof(int));
	for (auto elem: district_map) {
		elem.second->saveVotes(out);
	}
}

void DistrictArr::load(istream& in)
{
	int loaded_size;
	in.read(rcastc(&loaded_size), sizeof(loaded_size));
	DistrictType type;
	district_map.clear();//overrun the old 
	for (int i = 0; i < loaded_size; i++)
	{
		in.read(rcastc(&type), sizeof(type));
		switch (type) {
		case DistrictType::WTA:
		{
			District* new_dist_WTA = new WTADistrict(in);
			district_map.insert(pair<int, District*>(new_dist_WTA->getId(), new_dist_WTA));
			break;
		}
			
		case DistrictType::RELATIVE:
		{
			District* new_dist_relative = new RelativeDistrict(in);
			district_map.insert(pair<int, District*>(new_dist_relative->getId(), new_dist_relative));
			break;
		}
		}
	}
}

void DistrictArr::link(istream& in, const PartyArr& party_map)
{
	int votes_arr_size;
	in.read(rcastc(&votes_arr_size), sizeof(votes_arr_size));
	for (auto elem: district_map) {
	elem.second->link(in, party_map);
	}
}

const Citizen* DistrictArr::getCitizen(int id, int district_num)const
{
	if (district_map.find(district_num)!= district_map.end()) {
		return district_map.find(district_num)->second->getCitizen(id);// should throw if no citiz with this id
	}
	else
		throw invalid_argument("No District with this ID");
}

ostream& operator<<(ostream& os, const DistrictArr& arr) //printing citizens
{
	for (auto elem: arr.district_map)// moving in DistArr
	{
		for (auto citizen: elem.second->getCitizenArr().citizen_map)//in citizenArr
		{
			os << citizen.second << endl
				<< "***********************************" << endl;
		}
	}
	return os;
}

void DistrictArr::printDistricts() const
{
	for (auto elem : district_map)
	{
		cout << elem.second << endl;
	}
}
