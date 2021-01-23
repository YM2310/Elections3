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
}


PartyArr::~PartyArr()
{

}

int PartyArr::getLogSize() const
{
	return(party_arr.size());
}

const Party& PartyArr::getParty(int partyNum) const
{
	DynamicArray<PartyPtr>::const_iterator iter = party_arr.begin();
	DynamicArray<PartyPtr>::const_iterator end = party_arr.end();
	for (auto& party : party_arr)
	{
		if (party->getPartyNum() == partyNum)
			return *party;
	}
}

Party* PartyArr::addParty(myString& partyName, int _partyNum, const Citizen* leader)
{
	
	Party* new_party = new Party(partyName, leader, _partyNum);
	party_arr.push_back(new_party);
	return new_party;
}

void PartyArr::addDistrict(District* district_id)
{
	for (auto& party : party_arr)
	{
		party->addDistrict(district_id);
	}
}



int PartyArr::CheckIfRep(const Citizen* newrep)const { //gets a citizen we know exists and returns if they are a rep of a party
	for (auto& party : party_arr)
	{
		if (party->getLeader().getID() == newrep->getID())
			return 100;
		for (auto& reps_of_dist : party->getRepsArr().getReps())
		{
			for (auto& rep : reps_of_dist.citizen_arr)
			{
				if (rep->getID() == newrep->getID())
				{
					return 100;
				}
			}
		}
	}
	return 200;// not a rep 
}

int PartyArr::addRep(int party_num, int district_num, const Citizen* newrep)
{
	if (CheckIfRep(newrep) == 200)
	{
		for (auto& party : party_arr)
		{
			if (party->getPartyNum() == party_num)
			{
				return party->addRep(newrep, district_num);
			}
		}
	}
	else
		return 100; //This citizen is already a representative
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
}

void PartyArr::save(ostream& out) const
{
	int log_size = party_arr.size();
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (auto party : party_arr) {
		party->save(out);
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
