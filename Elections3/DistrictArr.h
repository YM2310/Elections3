#pragma once
#include "WTADistrict.h"
#include "RelativeDistrict.h"
#include "DistrictPtr.h"
#include <map>

class DistrictArr
{
public:
	DistrictArr(int size = 1);
	DistrictArr(istream& in); //load
	DistrictArr(const DistrictArr& origin) = delete;
	~DistrictArr();
	
	/*Getters:*/

	const District& getDistrict(int district_num) const;
	const Citizen* getCitizen(int id, int district_num = -1)const;

	/*Adders:*/
	
	District* addDistrict(string& name, int district_id, int electors, DistrictType type);
	int addCitizen(string& name, int id, int birthyear, int district_id);
	void addParty(const Party* partynum);
	int addVote(int party_num, int id);
	int addRep(int party_num, int id, int district_id);

	/*Files: */
	void saveDistricts(ostream& out)const;
	void saveVotes(ostream& out)const;
	void load(istream& in);
	void link(istream& in, const PartyArr& party_map);

	void printDistricts() const;

	/*Operators: */
	friend ostream& operator<<(ostream& os, const DistrictArr& arr);

	/*STL: */
	map<int, District*> district_map;

}; 
