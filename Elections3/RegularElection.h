#pragma once
#include "Election.h"

class RegularElection : public Election // As it was in the first project
{
public:
	RegularElection(myString& _date);
	RegularElection(istream& in); //load
	RegularElection();
	virtual ~RegularElection();

	/*Getters*/
	const DistrictArr& getDistrictArr() const;
	const District& getDistrict(int district_num)const;

	/*Adders: */
	void addDistrict(myString& name, int electors, DistrictType type);

	/*Printers: */
	void printDistricts() const;
	void printCitizens() const; //for the regular election


	virtual ostream& printResults(ostream& os) const override;
	void checkDistrictExists(int district) const; //relevant only to RegularElection
	virtual void save(ostream& out) const;

	virtual void sumElectors() override;

};
