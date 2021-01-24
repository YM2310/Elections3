
#include "DistrictArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

DistrictArr::DistrictArr(int size) :
	district_map {}
{
}

DistrictArr::DistrictArr(istream& in) { //load
	try {
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
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}


DistrictArr::~DistrictArr()
{
	for (auto elem : district_map) {
		delete elem.second;
	}
	district_map.clear();
}

const District& DistrictArr::getDistrict(int district_num) const
{
	if(district_map.find(district_num) == district_map.end())
		throw invalid_argument("No District with this ID");
	else {
		return *district_map.find(district_num)->second;
	}
}

District* DistrictArr::addDistrict(string& name, int district_id, int electors, DistrictType type)// pay attention: when you create the new arr, you are creating a new DistrictPtr* and NOT DistritctArr.
//so 1) dont delete existing arr, just its DistrictPtr* and 2) reassing just the DistrictPtr*
{
	try {
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
	catch (bad_alloc& ex)
	{
		throw;
	}
}

void DistrictArr::addCitizen(string& name, int id, int birthyear, int district_id)
{
	if (district_map.find(district_id) == district_map.end())
		throw invalid_argument("No District with this id");
	for (auto elem : district_map)
	{
		if (elem.second->getCitizenArr().citizen_map.find(id) != elem.second->getCitizenArr().citizen_map.end())
			throw invalid_argument("Citizen already exists");
	}
	district_map.find(district_id)->second->addCitizen(name, id, birthyear);
}

void DistrictArr::addParty(const Party* partynum)
{
	try {
		for (auto elem : district_map) {
			elem.second->addParty(partynum);
		}
	}
	catch (...) {
		throw;
	}
}

void DistrictArr::addVote(int party_num, int id)
{
	for (auto elem : district_map)
	{
		try {
			elem.second->addVote(party_num, id);
			return;
		}
		catch (exception& ex) {
			if (ex.what() == "This citizen has already voted") {
				throw ex;
			}
		}
		
	}
	throw "No citizen with this id";
	

}

void DistrictArr::addRep(int party_num, int id, int district_id)
{
	try {
		district_map.find(district_id)->second->addRep(party_num);
	}
	catch (...) {
		throw;
	}
}

void DistrictArr::saveDistricts(ostream& out)const
{
	try {
		int size = district_map.size();
		out.write(rcastcc(&size), sizeof(int));
		for (auto elem : district_map) {
			elem.second->save(out);
		}
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void DistrictArr::saveVotes(ostream& out)const
{
	try {
		int size = district_map.size();
		out.write(rcastcc(&size), sizeof(int));
		for (auto elem : district_map) {
			elem.second->saveVotes(out);
		}
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void DistrictArr::load(istream& in)
{
	try {
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
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void DistrictArr::link(istream& in, const PartyArr& party_map)
{
	try {
		int votes_arr_size;
		in.read(rcastc(&votes_arr_size), sizeof(votes_arr_size));
		for (auto elem : district_map) {
			elem.second->link(in, party_map);
		}
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

const Citizen* DistrictArr::getCitizen(int id, int district_num)const 
{
	if (district_num == -1) {
		for (auto& dist : district_map) {
			try { return dist.second->getCitizen(id); }
			catch (...) {};
		}
		throw invalid_argument("Citizen not found");
	}
	if (district_map.find(district_num)!= district_map.end()) {
		return district_map.find(district_num)->second->getCitizen(id);
	}
	else
		throw invalid_argument("No District with this ID");
}

ostream& operator<<(ostream& os, const DistrictArr& arr) //printing citizens
{
	for (auto& elem: arr.district_map)// moving in DistArr
	{
		for (auto& citizen: elem.second->getCitizenArr().citizen_map)//in citizenArr
		{
			os << *citizen.second << endl
				<< "***********************************" << endl;
		}
	}
	return os;
}

void DistrictArr::printDistricts() const
{
	for (auto elem : district_map)
	{
		cout << *elem.second << endl;
	}
}
