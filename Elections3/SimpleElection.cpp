#include "SimpleElection.h"
#define rcastc reinterpret_cast<char*> 
#define rcastcc reinterpret_cast<const char*> 
enum class ElectionType { REGULAR = 1, SIMPLE = 2 };

SimpleElection::SimpleElection(string& _date, int electors)
	: Election(_date)
{
	string name = "No Districts in simple elections";
	district_arr.addDistrict(name, 0, electors, DistrictType::RELATIVE); //2== RelativeDistrict
}

SimpleElection::SimpleElection(istream& in)
	: Election(in) //load
{
	//The adding of the district will happen on Election ctor
}

SimpleElection::~SimpleElection()
{

}

void SimpleElection::addCitizen(string& name, int id, int birthyear, int district_num)
{
	try {
		Election::addCitizen(name, id, birthyear, 0);
	}
	catch (...)
	{
		throw;
	}
}

void SimpleElection::addRep(int party_num, int id, int district_num)
{
	try {
		Election::addRep(party_num, id, 0);
	}
	catch (...){
		throw;
	}
}

ostream& SimpleElection::printResults(ostream& os) const
{
	cout << "***********************************" << endl;
	cout << "Election Type: Simple Election" << endl;
	for (int m = 0; m < party_arr.getLogSize(); m++)// moves in PartyArr
	{
		os << "Party Name: " << party_arr[m].getName() << endl <<
			"  Party Leader: " << party_arr[m].getLeader().getName() << endl <<
			"  Total number of chosen electors: " << party_arr[m].getElectorsWon() << endl <<
			"  List of chosen representatives: " << endl;
		for (int i = 0; i < party_arr[m].getElectorsWon(); i++) {
			os << i + 1 << ")." << party_arr[m].getRepsArr()[0].getNameOfRep(i) << endl;
		}
		os << "  Total number of votes: " << party_arr[m].getVotes() << endl <<
			"       Percentage from total votes: " << (static_cast<float>(party_arr[m].getVotes()) / static_cast<float>(district_arr[0].getTotalVotes())) * 100 << "%" << endl;
	}
	os << "-----------" << endl;

	return os;
}

void SimpleElection::sumElectors() {
	party_arr.quickSortByVotes(party_arr, 0, party_arr.getLogSize() - 1);
	Election::sumElectors();
}

void SimpleElection::save(ostream& out) const
{
	try {
		ElectionType type = ElectionType::SIMPLE;
		out.write(rcastcc(&type), sizeof(type));
		Election::save(out);
	}
	catch (ostream::failure& ex) { // Is this one correct???
		throw("Exception opening/writing/closing file");
	}
}
