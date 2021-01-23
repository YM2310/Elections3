#include "Party.h"
#include "DistrictArr.h"

Party::Party(string _name, const Citizen* _leader, int _party_num)
{
	party_num = _party_num;
	name = _name;
	leader = _leader;
	votes_got = 0;
	electors_won = 0;
}

Party::Party(istream& in, DistrictArr& district_map) //load
{
	in.read(rcastc(&party_num), sizeof(party_num));
	in.read(rcastc(&votes_got), sizeof(votes_got));
	in.read(rcastc(&electors_won), sizeof(electors_won));
	int leader_id;
	in.read(rcastc(&leader_id), sizeof(int));// ignore leader_id
	leader = district_map.getCitizen(leader_id);
	in.read(rcastc(&name), sizeof(name));

	reps_by_district.load(in, district_map);
}

void Party::addElectors(int won)
{
	electors_won += won;
}

void Party::addRep(const Citizen* rep, int district_num)
{
	try {
		reps_by_district.addRep(rep, district_num);
	}
	catch (...) {
		throw;
	}
}

void Party::addDistrict(const District* district_id)
{
	reps_by_district.addDistrict(district_id);
}

int Party::getVotes() const
{
	return votes_got;
}

int Party::getPartyNum() const
{
	return party_num;
}

int Party::getElectorsWon() const
{
	return electors_won;
}

const string& Party::getName() const
{
	return name;
}

const Citizen& Party::getLeader()const
{
	return *leader;;
}

const RepsArr& Party::getRepsArr() const
{
	return reps_by_district;
}

void Party::updateVotes(int add) {
	votes_got = add;
}

const Reps& Party::getReps(int district_num) const
{
	for (int i = 0; i < reps_by_district.getLogSize(); i++)
	{
		if (district_num == reps_by_district[i].getDistrictNum())
			return reps_by_district[i];
	}
}

void Party::resetElectors()
{
	electors_won = 0;
}

void Party::save(ostream& out)
{
	out.write(rcastcc(&party_num), sizeof(party_num));
	out.write(rcastcc(&votes_got), sizeof(votes_got));
	out.write(rcastcc(&electors_won), sizeof(electors_won));
	int leader_id = leader->getID();
	out.write(rcastcc(&leader_id), sizeof(int));
	out.write(rcastcc(&name), sizeof(name));
	reps_by_district.save(out);
}

ostream& operator<<(ostream& os, const Party& party)
{
	os << "***********************************" << endl;
	os << "Party Name: " << party.name << endl <<
		"Party Number: " << party.party_num << endl <<
		"Party Leader: " << party.leader->getName() << endl;
	for (int i = 0; i < party.getRepsArr().getLogSize(); i++)
	{
		os << " Representatives for District Number: " << party.getRepsArr()[i].getDistrictNum() << endl << "  ";
		for (int j = 0; j < party.getRepsArr()[i].getLogSize(); j++)// MAYBE HAVE AN ITR ON THE CITIZEN MAP?
			os << j + 1 << ")" << party.getRepsArr()[i].getNameOfRep(j) << "  ";
		os << endl;
	}
	os << "***********************************" << endl;
	return os;
}
