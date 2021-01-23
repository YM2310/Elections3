#pragma once
#include "CitizenArr.h"
#include "DistrictVotes.h"
#include <string>
#include <map>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
enum DistrictType { WTA = 1, RELATIVE = 2 };

class PartyArr;
class DistrictPtr;
class District
{
public:
	District(string& _name, int _id, int _electors);
	District(const District& origin) = delete;
	District(istream& in); //load
	District();
	virtual ~District() {};

	/*Getters: */
	const string& getName() const;
	int getId() const;
	int getElectors() const;
	int getTotalVotes() const;//Added
	float getVotingPercentage()const;
	virtual DistrictVotesArr getWinner()const = 0;
	const Citizen* getCitizen(int id) const;
	const CitizenArr& getCitizenArr() const;
	const DistrictVotesArr& getVotesArr() const;
	int getVotesOfParty(int party_num) const;

	/*Setters: */
	bool setName(const string& _name);
	bool setId(int _id);
	bool setElectors(int _electors);

	/*Adders: */
	void addCitizen(string& name, int id, int birthyear);
	void addCitizen(Citizen* citizen);
	void addParty(const Party* partynum);
	void addRep(int party_num);
	void addVote(int party_num, int id); /// verify id, and then vote! 

	/*Calculations: */
	float calcVotingPercent();
	void calculateReps();

	/*Files: */
	virtual void save(ostream& out) const;
	virtual void saveVotes(ostream& out) const;
	virtual void link(istream& in, const PartyArr& party_map);
	virtual void load(istream& in);

	/*Operators: */
	friend ostream& operator<<(ostream& os, const District& dist);
	virtual ostream& printDistrict(ostream& os) const;
	virtual ostream& printCitizens(ostream& os) const;

protected:
	int id;
	int electors;
	int total_votes;
	float voting_percent;

	string name;
	CitizenArr citizen_arr; 
	DistrictVotesArr votes_arr;
};
