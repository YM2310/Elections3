#include "Election.h"
#include "RegularElection.h"
#include "SimpleElection.h"
#include <iostream>
#include <typeinfo>

#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 

Election::Election(myString& _date)
{
	date = _date;
	new_party_id = 0;
	new_district_id = 0;
}

Election::Election()
{
	new_party_id = 0;
	new_district_id = 0;
}

Election::Election(istream& in) //load
{
	date.load(in);
	in.read(rcastc(&new_party_id), sizeof(new_party_id));
	in.read(rcastc(&new_district_id), sizeof(new_district_id));
	district_arr.load(in);
	party_arr.load(in,district_arr);
	district_arr.link(in, party_arr);
}

Election::~Election()
{

}

myString Election::getDate()const
{
	return date;
}

Party Election::getParty(int party_num)const
{
	return party_arr.getParty(party_num);
}

const PartyArr& Election::getPartyArr()const
{
	return party_arr;
}

void Election::setDate(myString date)
{
	this->date = date;
}


void Election::printPartys() const
{
	cout << party_arr;
}

bool Election::checkPartyExists(int party) const
{
	for (int i = 0; i < party_arr.getLogSize(); i++)
	{
		if (party_arr[i].getPartyNum() == party)
			return true;
	}
	return false;
}

void Election::printCitizens() const
{
	cout << district_arr; //this is for printing all citizens
}

int Election::addVote(int id, int party_num)
{
	return district_arr.addVote(party_num, id);
}

int Election::addCitizen(myString& name, int id, int birthyear, int district_num)
{
	return district_arr.addCitizen(name, id, birthyear, district_num);
}

int Election::addRep(int party_num, int rep_id, int district_num)
{
	const Citizen* rep_ptr = district_arr.getCitizen(rep_id);
	if (rep_ptr == nullptr)
		return 400; // citizen not found
	return party_arr.addRep(party_num, district_num, rep_ptr);
}

int Election::addParty(myString& name, int candidate_id)
{
	int party_id = new_party_id;
	const Citizen* leader = district_arr.getCitizen(candidate_id);

	if (leader == nullptr)
		return 400; // citizen not found
	if (party_arr.CheckIfRep(leader) == 200) {
		Party* new_party = party_arr.addParty(name, party_id, leader);
		district_arr.addParty(new_party);
		for (int i = 0; i < district_arr.getLogSize(); i++)
		{
			new_party->addDistrict(&district_arr[i]);
		}
		new_party_id++;
		return 200; //validates OK
	}
	else
		return 100; // already a representative
}

void Election::sumElectors()
{
	party_arr.initElectors();
	int winner, electors, party_votes;
	DistrictVotesArr electors_arr;
	for (int i = 0; i < district_arr.getLogSize(); i++) // within dist_arr
	{
		district_arr[i].calculateReps();
		electors_arr = district_arr[i].getWinner();
		for (int j = 0; j < electors_arr.getLogSize(); j++) { //within dist_votes_arr
			party_arr.addElectoralVotes(electors_arr[j].party->getPartyNum(), electors_arr[j].reps_num);
		}
		for (int j = 0; j < party_arr.getLogSize(); j++)// within party_arr
		{
			if (i == 0)//init the votes before adding
				party_arr[j].updateVotes(0);
			party_votes = district_arr[i].getVotesOfParty(party_arr[j].getPartyNum());
			party_arr[j].updateVotes(party_votes + party_arr[j].getVotes());
		}
	}
}

bool Election::checkReps() const// check if there are enough representatives
{
	for (int i = 0; i < district_arr.getLogSize(); i++)//moves on districts
	{
		for (int n = 0; n < district_arr[i].getVotesArr().getLogSize(); n++)//on VotesArr
		{
			if (district_arr[i].getVotesArr()[n].reps_num > district_arr[i].getVotesArr()[n].party->getRepsArr().getRepsOfDistrict(district_arr[i].getId()).getLogSize()) {
				return false;
			}
		}
	}
	return true;
}

void Election::save(ostream& out) const
{
	date.save(out);
	out.write(rcastcc(&new_party_id), sizeof(new_party_id));
	out.write(rcastcc(&new_district_id), sizeof(new_district_id));
	district_arr.saveDistricts(out);
	party_arr.save(out);
	district_arr.saveVotes(out);
}

void Election::load(istream& in)
{
	date.load(in);
	in.read(rcastc(&new_party_id), sizeof(new_party_id));
	in.read(rcastc(&new_district_id), sizeof(new_district_id));
	district_arr.load(in);
	party_arr.load(in, district_arr);
	district_arr.link(in, party_arr);
}

ostream& operator<<(ostream& os, const Election& elections)
{
	elections.printResults(os);
	return os;
}
