#pragma once
#include "myString.h"
#include "PartyArr.h"
#include "DistrictArr.h"

class Election {
public:
	Election(myString& _date);
	Election(istream& in);
	Election();
	virtual ~Election();
	
	/*Getters*/
	Party getParty(int party_num) const;
	const PartyArr& getPartyArr() const;
	myString getDate() const;
	bool checkReps() const;

	/*Adders*/
	virtual int addCitizen(myString& name, int id, int birthyear, int district_num);
	virtual int addRep(int party_num, int rep_id, int district_num);
	virtual int addParty(myString& name, int candidate_id);
	virtual void sumElectors();
	int addVote(int id, int party_num);

	/*Setters*/
	void setDate(myString date);

	/*Printers*/
	void printPartys() const;
	void printCitizens() const;
	virtual ostream& printResults(ostream& os)const = 0;
	friend ostream& operator<<(ostream& os, const Election& elections);

	bool checkPartyExists(int party) const;
	void save(ostream& out) const;
	void load(istream& in);

protected:
	int new_party_id;
	int new_district_id;
	myString date;
	PartyArr party_arr;
	DistrictArr district_arr;
};
