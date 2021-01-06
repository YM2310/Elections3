#pragma once
#include "citizenPtr.h"
#include "RepsArr.h"
class DistrictArr;
class Party
{
public:
	Party(myString name, const Citizen* leader, int party_num);
	Party(istream& in, DistrictArr& district_map); //load

	/*Getters: */
	int getVotes() const;
	int getPartyNum() const;
	int getElectorsWon() const;
	const Citizen& getLeader() const;
	const RepsArr& getRepsArr() const;
	const Reps& getReps(int district_num) const;
	const myString& getName() const;

	/*Adders*/
	void addElectors(int won);
	int addRep(const Citizen* rep, int district_num);
	void addDistrict(const District* district_id);

	/*Setters*/
	void updateVotes(int add);
	void resetElectors();

	/*Files: */
	void save(ostream& out);

	friend ostream& operator<<(ostream& os, const Party& party);
private:
	int party_num;
	int votes_got;
	int electors_won;
	const Citizen* leader; 
	myString name; //name of party
	RepsArr reps_by_district;// array of arrays of reps, each array is a district

};
