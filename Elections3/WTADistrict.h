#pragma once
#include "District.h"


class WTADistrict : public District {
public:
	WTADistrict(string& _name, int _id, int _electors);
	WTADistrict(istream& in); //load
	virtual ~WTADistrict();
	DistrictVotesArr getWinner() const override;
	virtual ostream& printDistrict(ostream& os) const override;
	virtual void save(ostream& out)const override;
	virtual void load(istream& in) override;
};
