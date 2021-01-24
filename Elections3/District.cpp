#include "District.h"
#include "PartyArr.h"
#include "CitizenArr.h"
#include "string.h"
#include "DistrictVotes.h"

District::District(string& _name, int _id, int _electors)
{
	id = _id;
	electors = _electors;
	name = _name;
	voting_percent = 0;
	total_votes = 0;
}

District::District(istream& in) //load
{
	try {
		in.read(rcastc(&id), sizeof(id));
		in.read(rcastc(&electors), sizeof(electors));
		in.read(rcastc(&total_votes), sizeof(total_votes));
		in.read(rcastc(&voting_percent), sizeof(voting_percent));
		int len;
		in.read(rcastc(&len), sizeof(int));
		char* temp = new char[len + 2];
		in.read(rcastc(temp), len);
		temp[len] = '\0';
		name = temp;
		delete[] temp;
		citizen_arr.load(in, this);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}


District::District()//new- only for init purposes (fix from 1st project)
{
	id = -2;
	electors = 0;
	name = "";
	voting_percent = 0;
	total_votes = 0;
}

const string& District::getName() const
{
	return name;
}

int District::getId() const
{
	return id;
}

int District::getElectors() const
{
	return electors;
}

float District::getVotingPercentage() const
{
	return static_cast<float>(total_votes) * 100 / citizen_arr.citizen_map.size();
}

const Citizen* District::getCitizen(int id) const
{
	auto iter = citizen_arr.citizen_map.find(id);
	if (iter == citizen_arr.citizen_map.end()) {
		throw invalid_argument("Citizen doesnt exist");
	}
	else {
		return iter->second;
	}
}

int District::getTotalVotes() const
{
	return total_votes;
}

bool District::setName(const string& _name)
{
	name = _name;
	return true;
}

bool District::setId(int _id)
{
	id = _id;
	return true;
}

bool District::setElectors(int _electors)
{
	electors = _electors;
	return true;
}

void District::addCitizen(string& name, int id, int birthyear)
{
	try {
		return citizen_arr.addCitizenToArr(name, id, birthyear, this);
	}
	catch (...) {
		throw;
	}
}

void District::addCitizen(Citizen* citizen)
{
	try {
		citizen_arr.addCitizenToArr(citizen);
	}
	catch (bad_alloc& ex) {
		throw;
	}
}

void District::addParty(const Party* partynum)
{
	try {
		votes_arr.addParty(partynum);
	}
	catch (...)
	{
		throw;
	}
}

void District::addVote(int party_num, int id)
{
	if (citizen_arr.citizen_map.find(id) == citizen_arr.citizen_map.end())
		throw invalid_argument("No citizen with this id");
	Citizen* citizen = citizen_arr.citizen_map.find(id)->second;
	if (citizen->getIfVoted())
		throw true;

	citizen->setIfVoted(true);
	votes_arr.addVote(party_num);
	total_votes++;
	return;
}

void District::addRep(int party_num)
{
	try {
		votes_arr.addRep(party_num);
	}
	catch (...) {
		throw;
	}
}

float District::calcVotingPercent()
{
	return voting_percent;
}

void District::calculateReps()
{
	int reps_left = electors;
	float votes_per_rep = static_cast<float>(total_votes) / static_cast<float>(electors);
	if (votes_per_rep == 0) {// this is if no one voted yet
		int lowest_id = 0;
		for (int i = 0; i < votes_arr.getLogSize() - 1; i++)
		{
			if (votes_arr[i + 1].party->getPartyNum() < votes_arr[i].party->getPartyNum())
				lowest_id = i;
		}
		votes_arr[lowest_id].reps_num = electors;
		return;
	}
	for (int i = 0; i < votes_arr.getLogSize(); i++)
	{
		votes_arr[i].reps_num = static_cast<int>((votes_arr[i].votes) / (votes_per_rep));
		reps_left -= votes_arr[i].reps_num;
		if (reps_left == 0)
			break;
	}
	votes_arr.bubbleReminder(votes_per_rep, reps_left);
	for (int i = 0; i < reps_left; i++)
	{
		votes_arr[i % votes_arr.getLogSize()].reps_num++;// mod so it will go back to 1 if more reps left than parties exist
	}
	quickSort(votes_arr.begin(), votes_arr.end() - 1, DistrictVotesArr::cmpDistrictVotes());
}

void District::save(ostream& out) const
{
	try {
		out.write(rcastcc(&id), sizeof(id));
		out.write(rcastcc(&electors), sizeof(electors));
		out.write(rcastcc(&total_votes), sizeof(total_votes));
		out.write(rcastcc(&voting_percent), sizeof(voting_percent));
		int len = name.size();
		out.write(rcastcc(&len), sizeof(int));
		out.write(rcastcc(&name[0]), len);
		citizen_arr.save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void District::saveVotes(ostream& out) const
{
	try {
		votes_arr.save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}


void District::link(istream& in, const PartyArr& party_map)
{
	try {
		votes_arr.load(in, party_map);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void District::load(istream& in)
{
	try {
		in.read(rcastc(&id), sizeof(id));
		in.read(rcastc(&electors), sizeof(electors));
		in.read(rcastc(&total_votes), sizeof(total_votes));
		in.read(rcastc(&voting_percent), sizeof(voting_percent));
		int len;
		in.read(rcastc(&len), sizeof(int));
		char* temp = new char[len + 2];
		in.read(rcastc(temp), len);
		temp[len] = '\0';
		name = temp;
		delete[] temp;
		citizen_arr.load(in, this);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
	catch (std::bad_alloc& ba)
	{
		throw ba;
	}

}


const DistrictVotesArr& District::getVotesArr()const
{
	return votes_arr;
}

int District::getVotesOfParty(int party_num) const
{
	return votes_arr.getVotes(party_num);
}

const CitizenArr& District::getCitizenArr() const
{
	return citizen_arr;
}

ostream& operator<<(ostream& os, const District& dist)
{
	dist.printDistrict(os);
	return os;
}

ostream& District::printDistrict(ostream& os) const
{
	os << "District Number: " << id <<
		"  District Name: " << name <<
		"  Number of representatives: " << electors << endl <<
		"***********************************" << endl;
	return os;
}

ostream& District::printCitizens(ostream& os) const
{
	for (auto& citizen : citizen_arr.citizen_map)//in citizenArr
	{
		os << citizen.second << endl
			<< "***********************************" << endl;
	}
	return os;
}