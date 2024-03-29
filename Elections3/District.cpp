#include "District.h"
#include "PartyArr.h"
#include "CitizenArr.h"
#include "myString.h"
#include "DistrictVotes.h"

District::District(myString& _name, int _id, int _electors)
{
	id = _id;
	electors = _electors;
	name = _name;
	voting_percent = 0;
	total_votes = 0;
}

District::District(istream& in) //load
{
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&electors), sizeof(electors));
	in.read(rcastc(&total_votes), sizeof(total_votes));
	in.read(rcastc(&voting_percent), sizeof(voting_percent));
	name.load(in);
	citizen_arr.load(in,this);

}


District::District()//new- only for init purposes (fix from 1st project)
{
	id = -2;
	electors = 0;
	name = "";
	voting_percent = 0;
	total_votes = 0;
}

const myString& District::getName() const
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
	return static_cast<float>(total_votes) * 100 / citizen_arr.getLogSize();
}

const Citizen* District::getCitizen(int id) const
{
	return citizen_arr.getCitizenByID(id);
}

int District::getTotalVotes() const
{
	return total_votes;
}

bool District::setName(const myString& _name)
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

int District::addCitizen(myString& name, int id, int birthyear)
{
	return citizen_arr.addCitizenToArr(name, id, birthyear, this);
}

int District::addCitizen(Citizen* citizen)
{
	return citizen_arr.addCitizenToArr(citizen);
}

void District::addParty(const Party* partynum)
{
	votes_arr.addParty(partynum);
}

int District::addVote(int party_num, int id)
{
	Citizen* citizen = citizen_arr.getCitizenByID(id);
	if (citizen == nullptr)
		return 400; //No such citizen
	if (citizen->getIfVoted())
		return 100; // already voted

	citizen->setIfVoted(true);
	votes_arr.addVote(party_num);
	total_votes++;
	return 200;

}

int District::addRep(int party_num)
{
	return votes_arr.addRep(party_num);
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
		votes_arr[i% votes_arr.getLogSize()].reps_num++;// mod so it will go back to 1 if more reps left than parties exist
	}
	votes_arr.qSort();
}

void District::save(ostream& out) const
{
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&electors), sizeof(electors));
	out.write(rcastcc(&total_votes), sizeof(total_votes));
	out.write(rcastcc(&voting_percent), sizeof(voting_percent));

	name.save(out);
	citizen_arr.save(out);
}

void District::saveVotes(ostream& out) const
{
	votes_arr.save(out);
}


void District::link(istream& in, const PartyArr& party_map)
{

	votes_arr.load(in, party_map);
	
}

void District::load(istream& in)
{
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&electors), sizeof(electors));
	in.read(rcastc(&total_votes), sizeof(total_votes));
	in.read(rcastc(&voting_percent), sizeof(voting_percent));
	name.load(in);
	citizen_arr.load(in, this);
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
