#include "PartyArr.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

PartyArr::PartyArr(int _logsize, int _realsize)
{
	log_size = _logsize;
	real_size = _realsize;
	party_arr = new PartyPtr[real_size];
}

PartyArr::PartyArr(istream& in, DistrictArr& district_map)// load
{
	in.read(rcastc(&log_size), sizeof(log_size));
	real_size = log_size + 1;
	party_arr = new PartyPtr[real_size];
	for (int i = 0; i < log_size; i++)
	{
		Party* party = new Party(in, district_map);
		party_arr[i].setPtr(party);
	}
}


PartyArr::~PartyArr()
{
	delete[] party_arr;
}

int PartyArr::getLogSize() const
{
	return(log_size);
}

Party& PartyArr::getParty(int partyNum) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (party_arr[i]->getPartyNum() == partyNum)
			return *party_arr[i];
	}
}

Party* PartyArr::addParty(string& partyName, int _partyNum, const Citizen* leader)
{
	if (log_size == real_size)
		doubleSize();
	Party* new_party = new Party(partyName, leader, _partyNum);
	party_arr[log_size].setPtr(new_party);

	log_size++;//so the first one added to PartyArr will be in idx 0
	return new_party;
}

void PartyArr::addDistrict(District* district_id)
{
	for (int i = 0; i < log_size; i++)
	{
		party_arr[i]->addDistrict(district_id);
	}
	PartyPtr temp;
}

void PartyArr::doubleSize()
{
	changeSize(real_size * 2);
}

int PartyArr::CheckIfRep(const Citizen* newrep)const { //gets a citizen we know exists and returns if they are a rep of a party
	for (int j = 0; j < log_size; j++)
	{
		for (int m = 0; m < party_arr[j]->getRepsArr().getLogSize(); m++)
		{
			for (int n = 0; n < party_arr[j]->getRepsArr()[m].getLogSize(); n++)
			{
				if (party_arr[j]->getRepsArr()[m].getIDRep(n) == newrep->getID())
				{
					return 100;
				}
			}
		}
		if (party_arr[j]->getLeader().getID() == newrep->getID())
			return 100;
	}
	return 200;// not a rep 
}

int PartyArr::addRep(int party_num, int district_num, const Citizen* newrep)
{
	if (CheckIfRep(newrep) == 200)
	{
		for (int i = 0; i < log_size; i++)
		{
			if (party_arr[i]->getPartyNum() == party_num)
			{
				return party_arr[i]->addRep(newrep, district_num);
			}
		}
	}
	else
		return 100; //This citizen is already a representative
}

void PartyArr::addElectoralVotes(int party_num, int electors)
{
	for (int i = 0; i < log_size; i++)
	{
		if (party_arr[i]->getPartyNum() == party_num)
		{
			party_arr[party_num]->addElectors(electors);
		}
	}
}

void PartyArr::addVotes(int party_num, int votes)
{
	for (int i = 0; i < log_size; i++)
	{
		if (party_arr[i]->getPartyNum() == party_num)
		{
			party_arr[party_num]->updateVotes(votes);
		}
	}
}

int PartyArr::partition(PartyArr& arr, int left, int right)
{
	Party* tmp;
	Party& pivot = arr[right];
	int i = (left - 1);

	for (int j = left; j < right; j++)
	{
		if (arr[j].getElectorsWon() > pivot.getElectorsWon())
		{
			i++;
			tmp = &arr[i];
			arr.party_arr[i].setPtr(&arr[j]);
			arr.party_arr[j].setPtr(tmp);

		}
		if (arr[j].getElectorsWon() == pivot.getElectorsWon())
		{
			if (arr[j].getPartyNum() < pivot.getPartyNum())//handles daw
			{
				i++;
				tmp = &arr[i];
				arr.party_arr[i].setPtr(&arr[j]);
				arr.party_arr[j].setPtr(tmp);
			}
		}
	}
	tmp = &arr[i + 1];
	arr.party_arr[i + 1].setPtr(&arr[right]);
	arr.party_arr[right].setPtr(tmp);
	return (i + 1);
}

void PartyArr::quickSort(PartyArr& arr, int left, int right)
{
	if (left < right)
	{
		int pivot = partition(arr, left, right);
		quickSort(arr, left, pivot - 1);
		quickSort(arr, pivot + 1, right);
	}
}

void PartyArr::save(ostream& out) const
{
	out.write(rcastcc(&log_size), sizeof(log_size));
	for (int i = 0; i < log_size; ++i) {
		party_arr[i]->save(out);
	}
}

void PartyArr::load(istream& in, DistrictArr& district_map)
{
	int loaded_size;
	in.read(rcastc(&loaded_size), sizeof(loaded_size));
	real_size = loaded_size + 1;
	changeSize(real_size);
	log_size = loaded_size;

	for (int i = 0; i < log_size; i++)
	{
		party_arr[i].deleteParty();
		Party* party = new Party(in, district_map);
		party_arr[i].setPtr(party);
	}
}

void PartyArr::initElectors()
{
	for (int i = 0; i < log_size; i++)
	{
		party_arr[i]->resetElectors();
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

int PartyArr::partitionByVotes(PartyArr& arr, int left, int right)
{
	Party* tmp;
	Party& pivot = arr[right];
	int i = (left - 1);

	for (int j = left; j < right; j++)
	{
		if (arr[j].getVotes() > pivot.getVotes())
		{
			i++;
			tmp = &arr[i];
			arr.party_arr[i].setPtr(&arr[j]);
			arr.party_arr[j].setPtr(tmp);

		}
		if (arr[j].getVotes() == pivot.getVotes())
		{
			if (arr[j].getPartyNum() < pivot.getPartyNum())//handles daw
			{
				i++;
				tmp = &arr[i];
				arr.party_arr[i].setPtr(&arr[j]);
				arr.party_arr[j].setPtr(tmp);
			}
		}
	}
	tmp = &arr[i + 1];
	arr.party_arr[i + 1].setPtr(&arr[right]);
	arr.party_arr[right].setPtr(tmp);
	return (i + 1);
}

void PartyArr::changeSize(int size)
{
	real_size = size;
	PartyPtr* new_size = new PartyPtr[real_size];
	memcpy(new_size, party_arr, sizeof(PartyPtr) * log_size);
	for (int i = 0; i < log_size; i++)
	{
		party_arr[i].setPtr(nullptr);
	}
	delete[] party_arr; // <-- THIS
	party_arr = new_size; // <-- THIS
}

void PartyArr::quickSortByVotes(PartyArr& arr, int left, int right)
{
	if (left < right)
	{
		int pivot = partitionByVotes(arr, left, right);
		quickSortByVotes(arr, left, pivot - 1);
		quickSortByVotes(arr, pivot + 1, right);
	}
}
