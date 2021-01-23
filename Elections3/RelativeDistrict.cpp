#include "RelativeDistrict.h"

RelativeDistrict::RelativeDistrict(string& _name, int _id, int _electors) : District(_name, _id, _electors)
{
}

RelativeDistrict::RelativeDistrict(istream& in) : District(in) //load
{
}


RelativeDistrict::~RelativeDistrict()
{
}

DistrictVotesArr RelativeDistrict::getWinner() const
{
	return getVotesArr();
}

ostream& RelativeDistrict::printDistrict(ostream& os) const
{
	cout << "***********************************" << endl;
	cout << "District Type: Relative " << endl;
	this->District::printDistrict(os);
	return os;
}

void RelativeDistrict::save(ostream& out) const
{
	try {
		DistrictType temp = RELATIVE;
		out.write(rcastcc(&temp), sizeof(RELATIVE));
		District::save(out);
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}
void RelativeDistrict::load(istream& in)
{
	try {
		District::load(in);
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}
