#include "RegularElection.h"

#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 
enum class ElectionType { REGULAR = 1, SIMPLE = 2 };

RegularElection::RegularElection(myString& _date) : Election(_date)
{

}

RegularElection::RegularElection()
{

}

RegularElection::RegularElection(istream& in)
	: Election(in) //load
{

}

RegularElection::~RegularElection()
{

}

const DistrictArr& RegularElection::getDistrictArr() const
{
	return district_arr;
}

const District& RegularElection::getDistrict(int district_num) const
{
	return district_arr.getDistrict(district_num);
}

int RegularElection::addDistrict(myString& name, int electors, DistrictType type)
{
	int district_id = new_district_id;

	party_arr.addDistrict(district_arr.addDistrict(name, district_id, electors, type));
	new_district_id++;
	return 200; //validates
}

void RegularElection::printDistricts() const
{
	district_arr.printDistricts();
}

void RegularElection::printCitizens() const
{
	cout << district_arr; //this is for printing all citizens
}

bool RegularElection::checkDistrictExists(int district) const
{
	for (int i = 0; i < district_arr.getLogSize(); i++)
	{
		if (district_arr[i].getId() == district)
			return true;
	}
	return false;
}

ostream& RegularElection::printResults(ostream& os) const
{
	cout << "***********************************" << endl;
	cout << "Election Type: Regular Election" << endl;
	int chosenElectors = 0;
	for (int i = 0; i < district_arr.getLogSize(); i++)// moves in DistrctArr
	{
		os << "***********************************" << endl <<
			"District Name: " << district_arr[i].getName() << endl <<
			"  Number of electors: " << district_arr[i].getElectors() << endl;

		if (typeid(district_arr[i]) == typeid(WTADistrict))
			os << "  District winner: " << district_arr[i].getWinner()[0].party->getLeader().getName() << endl;
		if (typeid(district_arr[i]) == typeid(RelativeDistrict)) {
			os << "Electors distribution: " << endl;
			const DistrictVotesArr& electors_dist = district_arr[i].getWinner();
			for (int j = 0; j < electors_dist.getLogSize(); j++)
			{
				os << " " << electors_dist[j].party->getLeader().getName() << ": " << electors_dist[j].reps_num << endl;
			}
		}

		os << "  Total votes in district:" << district_arr[i].getTotalVotes() << endl <<
			"  Voting percentage in district: " << district_arr[i].getVotingPercentage() << "%" << endl <<
			"  Elected representitives per party: " << endl;
		for (int j = 0; j < district_arr[i].getVotesArr().getLogSize(); j++)// moves in VotesArr
		{
			os << "    Party Name: " << district_arr[i].getVotesArr()[j].party->getName() << endl <<
				"     List of chosen representatives: " << endl << "       ";
			for (int m = 0; m < district_arr[i].getVotesArr()[j].reps_num; m++)// moves in RepsArr - print names of reps for each party
			{
				os << m + 1 << ")." << district_arr[i].getVotesArr()[j].party->getReps(district_arr[i].getId()).getNameOfRep(m) << " ";
			}
			os << endl << "     Number of votes: " << district_arr[i].getVotesArr()[j].votes << endl <<
				"     Percentage from total votes: " <<
				(static_cast<float>(district_arr[i].getVotesArr()[j].votes * 100) / static_cast<float>(district_arr[i].getTotalVotes())) << "%" << endl << endl;
		}
	}
	os << "-----------" << endl;
	for (int m = 0; m < party_arr.getLogSize(); m++)// moves in PartyArr
	{
		os << "Party Name: " << party_arr[m].getName() << endl <<
			"Party Leader: " << party_arr[m].getLeader().getName() << endl <<
			"Total number of chosen electors: " << party_arr[m].getElectorsWon() << endl <<
			"Total number of votes: " << party_arr[m].getVotes() << endl;
	}
	return os;
}

void RegularElection::save(ostream& out) const
{
	ElectionType type = ElectionType::REGULAR;
	out.write(rcastcc(&type), sizeof(type));
	Election::save(out);
}

void RegularElection::sumElectors() {
	party_arr.quickSort(party_arr, 0, party_arr.getLogSize() - 1);
	Election::sumElectors();
}
