#pragma once
#include "PartyArr.h"
#include "DistrictArr.h"
#include <string>
#include <map>

class Election {
public:
	Election(string& _date);
	Election(istream& in);
	Election();
	virtual ~Election();

	/*Getters*/
	Party getParty(int party_num) const;
	const PartyArr& getPartyArr() const;
	string getDate() const;
	void checkReps() const;

	/*Adders*/
	virtual void addCitizen(string& name, int id, int birthyear, int district_num);
	virtual void addRep(int party_num, int rep_id, int district_num);
	virtual void addParty(string& name, int candidate_id);
	virtual void sumElectors();
	void addVote(int id, int party_num);

	/*Setters*/
	void setDate(string date);

	/*Printers*/
	void printPartys() const;
	void printCitizens() const;
	virtual ostream& printResults(ostream& os)const = 0;
	friend ostream& operator<<(ostream& os, const Election& elections);

	void checkPartyExists(int party) const;
	void checkBirthYear(int _birthyear) const;
	void save(ostream& out) const;
	void load(istream& in);

protected:
	int new_party_id;
	int new_district_id;
	string date;
	PartyArr party_arr;
	DistrictArr district_arr;
};
