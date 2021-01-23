#include "WTADistrict.h"

WTADistrict::WTADistrict(string& _name, int _id, int _electors) :District(_name, _id, _electors)
{
}

WTADistrict::WTADistrict(istream& in) : District(in) //load
{
}

WTADistrict::~WTADistrict()
{
}

DistrictVotesArr WTADistrict::getWinner() const
{
	DistrictVotesArr winner;
	winner.addParty(getVotesArr()[0].party);
	winner[0].reps_num = electors;

	return winner;
}

ostream& WTADistrict::printDistrict(ostream& os) const
{
	cout << "***********************************" << endl;
	cout << "District Type: Winner Takes All" << endl;
	this->District::printDistrict(os);
	return os;
}

void WTADistrict::save(ostream& out) const
{
	try {
		DistrictType temp = WTA;
		out.write(rcastcc(&temp), sizeof(WTA));
		District::save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void WTADistrict::load(istream& in)
{
	try {
		District::load(in);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}
