#pragma once
#include "Election.h"
#include "RelativeDistrict.h"

class SimpleElection : public Election // With no districts
{
public:
	SimpleElection(myString& _date, int electors);
	SimpleElection(istream& in); //load
	virtual ~SimpleElection();

	/*Adders: */
	virtual void addCitizen(myString& name, int id, int birthyear, int district_num) override;//disregard the ditrict_num
	virtual void addRep(int party_num, int id, int district_num) override;//disregard the ditrict_num

	virtual ostream& printResults(ostream& os) const override;
	virtual void sumElectors() override;
	virtual void save(ostream& out) const;

};
