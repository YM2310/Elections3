#pragma once
#include "District.h"

class RelativeDistrict : public District {
public:
	RelativeDistrict(string& _name, int _id, int _electors);
	RelativeDistrict(istream& in);
	virtual ~RelativeDistrict();
	DistrictVotesArr getWinner() const override;
	ostream& printDistrict(ostream& os) const override;
	void save(ostream& out) const;
	void load(istream& in) override;
};
