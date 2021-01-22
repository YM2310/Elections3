#include "Election.h"
#include "RegularElection.h"
#include "SimpleElection.h"
#include <iostream>
#include <typeinfo>

#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 

Election::Election(string& _date)
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
	try {
		in.read(rcastc(&date), sizeof(date));
		in.read(rcastc(&new_party_id), sizeof(new_party_id));
		in.read(rcastc(&new_district_id), sizeof(new_district_id));
		district_arr.load(in);
		party_arr.load(in, district_arr);
		district_arr.link(in, party_arr);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

Election::~Election()
{

}

string Election::getDate()const
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

void Election::setDate(string date)
{
	this->date = date;
}

void Election::printPartys() const
{
	cout << party_arr;
}

void Election::checkPartyExists(int party) const
{
	for (int i = 0; i < party_arr.getLogSize(); i++)
	{
		if (party_arr[i].getPartyNum() == party)
			return;
	}
	throw "Party not found";
	throw "Party not found";
}

void Election::printCitizens() const
{
	cout << district_arr; //this is for printing all citizens
}

void Election::addVote(int id, int party_num)
{
	try {
		district_arr.addVote(party_num, id);
	}
	catch (...) { //so we can also catch string& msg , exception& ex - every option will be displayed in the menu!
		throw;
	}
}

void Election::addCitizen(string& name, int id, int birthyear, int district_num)
{
	try {
		checkBirthYear(birthyear);// throw an error if less than 18 years old
		district_arr.addCitizen(name, id, birthyear, district_num);
	}
	catch (...) {
		throw;
	}
}

void Election::addRep(int party_num, int rep_id, int district_num)
{
	try {
		const Citizen* rep_ptr = district_arr.getCitizen(rep_id);
		party_arr.addRep(party_num, district_num, rep_ptr);
	}
	catch (...) {
		throw;
	}
}

void Election::addParty(string& name, int candidate_id)
{
	try {
		int party_id = new_party_id;
		const Citizen* leader = district_arr.getCitizen(candidate_id); //try
		party_arr.CheckIfRep(leader); // try
		Party* new_party = party_arr.addParty(name, party_id, leader);
		district_arr.addParty(new_party);
		for (auto dist: district_arr.district_map)
		{
			new_party->addDistrict(dist.second);
		}
		new_party_id++;
	}
	catch (...) {
		throw;
	}
}

void Election::sumElectors()
{
	party_arr.initElectors();
	int winner, electors, party_votes, i = 0;
	DistrictVotesArr electors_arr;
	for (auto dist: district_arr.district_map) // within dist_arr
	{
		dist.second->calculateReps();
		electors_arr = dist.second->getWinner();
		for (int j = 0; j < electors_arr.getLogSize(); j++) { //within dist_votes_arr
			party_arr.addElectoralVotes(electors_arr[j].party->getPartyNum(), electors_arr[j].reps_num);
		}
		for (int j = 0; j < party_arr.getLogSize(); j++)// within party_arr
		{
			if (i == 0)//init the votes before adding
				party_arr[j].updateVotes(0);
			party_votes = dist.second->getVotesOfParty(party_arr[j].getPartyNum());
			party_arr[j].updateVotes(party_votes + party_arr[j].getVotes());
		}
		i++;
	}
}

void Election::checkReps() const// check if there are enough representatives
{
	for (auto dist : district_arr.district_map)//moves on districts
	{
		for (int n = 0; n < dist.second->getVotesArr().getLogSize(); n++)//on VotesArr
		{
			if (dist.second->getVotesArr()[n].reps_num > dist.second->getVotesArr()[n].party->getRepsArr().getRepsOfDistrict(dist.second->getId()).getLogSize()) {
				throw "Not enough representatives";
			}
		}
	}
	return;
}

void Election::save(ostream& out) const
{
	try {
		out.write(rcastcc(&date), sizeof(date));
		out.write(rcastcc(&new_party_id), sizeof(new_party_id));
		out.write(rcastcc(&new_district_id), sizeof(new_district_id));
		district_arr.saveDistricts(out);
		party_arr.save(out);
		district_arr.saveVotes(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/writing/closing file");
	}
}

void Election::load(istream& in)
{
	try {
		in.read(rcastc(&date), sizeof(date));
		in.read(rcastc(&new_party_id), sizeof(new_party_id));
		in.read(rcastc(&new_district_id), sizeof(new_district_id));
		district_arr.load(in);
		party_arr.load(in, district_arr);
		district_arr.link(in, party_arr);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

ostream& operator<<(ostream& os, const Election& elections)
{
	elections.printResults(os);
	return os;
}

void Election::checkBirthYear(int _birthyear) const
{
	int year = 0;
	year = (date[6] * 1000 + date[7] * 100 + date[8] * 10 + date[9]) - '0';
	if (year - _birthyear < 18)
		throw invalid_argument("Invalid birth year");
}
