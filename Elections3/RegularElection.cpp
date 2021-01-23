#include "RegularElection.h"
#include "QuickSort.h"
#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 
enum class ElectionType { REGULAR = 1, SIMPLE = 2 };

RegularElection::RegularElection(string& _date) : Election(_date)
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

void RegularElection::addDistrict(string& name, int electors, DistrictType type)
{
	int district_id = new_district_id;
	party_arr.addDistrict(district_arr.addDistrict(name, district_id, electors, type));
	new_district_id++;
}

void RegularElection::printDistricts() const
{
	district_arr.printDistricts();
}

void RegularElection::printCitizens() const
{
	cout << district_arr; //this is for printing all citizens
}

void RegularElection::checkDistrictExists(int district) const
{
	if(district_arr.district_map.find(district) == district_arr.district_map.end())
		throw "District not found";
}

ostream& RegularElection::printResults(ostream& os) const
{
	cout << "***********************************" << endl;
	cout << "Election Type: Regular Election" << endl;
	int chosenElectors = 0;
	for (auto dist: district_arr.district_map)// moves in DistrctArr
	{
		os << "***********************************" << endl <<
			"District Name: " << dist.second->getName() << endl <<
			"  Number of electors: " << dist.second->getElectors() << endl;

		if (typeid(*(dist.second)) == typeid(WTADistrict))
			os << "  District winner: " << dist.second->getWinner()[0].party->getLeader().getName() << endl;
		if (typeid(*(dist.second)) == typeid(RelativeDistrict)) {
			os << "Electors distribution: " << endl;
			const DistrictVotesArr& electors_dist = dist.second->getWinner();
			for (int j = 0; j < electors_dist.getLogSize(); j++)
			{
				os << " " << electors_dist[j].party->getLeader().getName() << ": " << electors_dist[j].reps_num << endl;
			}
		}

		os << "  Total votes in district:" << dist.second->getTotalVotes() << endl <<
			"  Voting percentage in district: " << dist.second->getVotingPercentage() << "%" << endl <<
			"  Elected representitives per party: " << endl;
		for (int j = 0; j < dist.second->getVotesArr().getLogSize(); j++)// moves in VotesArr
		{
			os << "    Party Name: " << dist.second->getVotesArr()[j].party->getName() << endl <<
				"     List of chosen representatives: " << endl << "       ";
			for (int m = 0; m < dist.second->getVotesArr()[j].reps_num; m++)// moves in RepsArr - print names of reps for each party
			{
				os << m + 1 << ")." << dist.second->getVotesArr()[j].party->getReps(dist.second->getId()).getNameOfRep(m) << " ";
			}
			os << endl << "     Number of votes: " << dist.second->getVotesArr()[j].votes << endl <<
				"     Percentage from total votes: " <<
				(static_cast<float>(dist.second->getVotesArr()[j].votes * 100) / static_cast<float>(dist.second->getTotalVotes())) << "%" << endl << endl;
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
	try {
		ElectionType type = ElectionType::REGULAR;
		out.write(rcastcc(&type), sizeof(type));
		Election::save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/writing/closing file");
	}
}

void RegularElection::sumElectors() {
	Election::sumElectors();
	quickSort(party_arr.begin(), party_arr.end()-1, PartyArr::CmpElectors());
}
