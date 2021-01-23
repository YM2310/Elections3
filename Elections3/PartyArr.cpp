#include "PartyArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

PartyArr::PartyArr(int size) : party_arr(size)
{
	
}

PartyArr::PartyArr(istream& in, DistrictArr& district_map)// load
{
	int log_size;
	in.read(rcastc(&log_size), sizeof(log_size));
	for (int i = 0; i < log_size; i++)
	{
		Party* party = new Party(in, district_map);
		party_arr.push_back(party);
	}
	if (in.good() == false) {
		for (auto party : party_arr) {
			party.deleteParty();
		}
		party_arr.~DynamicArray();
		throw runtime_error("file not good!");
	}
}


PartyArr::~PartyArr()
{

}

void PartyArr::clearParties()
{
	for (auto partyptr : party_arr) {
		partyptr.deleteParty();
	}
}

int PartyArr::getLogSize() const
{
	return(party_arr.size());
}

const Party& PartyArr::getParty(int partyNum) const
{
	for (auto& party : party_arr)
	{
		if (party->getPartyNum() == partyNum)
			return *party;
	}
	throw invalid_argument("Party doesnt exist");
}

Party* PartyArr::addParty(myString& partyName, int _partyNum, const Citizen* leader)
{
	
	Party* new_party = new Party(partyName, leader, _partyNum);
	PartyPtr temp_ptr(new_party);
	party_arr.push_back(temp_ptr);
	temp_ptr = nullptr;
	return new_party;
}

void PartyArr::addDistrict(District* district_id)
{
	for (auto& party : party_arr)
	{
		party->addDistrict(district_id);
	}
}



bool PartyArr::CheckIfRep(const Citizen* newrep)const { //gets a citizen we know exists and returns if they are a rep of a party
	for (auto& party : party_arr)
	{
		if (party->getLeader().getID() == newrep->getID())
			return true;
		for (auto& reps_of_dist : party->getRepsArr().getReps())
		{
			for (auto& rep : reps_of_dist.getAllReps())
			{
				if (rep->getID() == newrep->getID())
				{
					return true;
				}
			}
		}
	}
	return false;// not a rep 
}

void PartyArr::addRep(int party_num, int district_num, const Citizen* newrep)
{
	if (!CheckIfRep(newrep))
	{
		for (auto& party : party_arr)
		{
			if (party->getPartyNum() == party_num)
			{
				 party->addRep(newrep, district_num);
			}
		}
	}
	else
		throw invalid_argument("Person already a rep"); //This citizen is already a representative
}

void PartyArr::addElectoralVotes(int party_num, int electors)
{
	for (auto& party:party_arr)
	{
		if (party->getPartyNum() == party_num)
		{
			party->addElectors(electors);
		}
	}
	throw invalid_argument("Party doesnt exist");
}

void PartyArr::addVotes(int party_num, int votes)
{
	for (auto& party : party_arr)
	{
		if (party->getPartyNum() == party_num)
		{
			party->updateVotes(votes);
		}
	}
	throw invalid_argument("Party doesnt exist");
}

void PartyArr::save(ostream& out) const
{
	int log_size = party_arr.size();
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (auto party : party_arr) {
		party->save(out);
	}

	if (out.good() == false) {
		throw runtime_error("file not good!");
	}
}

void PartyArr::load(istream& in, DistrictArr& district_map)
{
	int loaded_size;
	in.read(rcastc(&loaded_size), sizeof(loaded_size));

	for (int i = 0; i < loaded_size; i++)
	{
		Party* party = new Party(in, district_map);
		party_arr.push_back(party);
	}
	if (in.good() == false) {
		for (auto party : party_arr) {
			party.deleteParty();
		}
		party_arr.~DynamicArray();
		throw runtime_error("file not good!");
	}
}

void PartyArr::initElectors() 
{
	for (auto& party : party_arr)
	{
		party->resetElectors();
	}
}

ostream& operator<<(ostream& os, const PartyArr& arr)
{
	for (int i = 0; i < arr.getLogSize(); i++)//in PartyArr
	{
		os << arr[i];
	}
	return os;
}
