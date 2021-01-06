#pragma once
#include "WTADistrict.h"
#include "RelativeDistrict.h"
#include "DistrictPtr.h"

class DistrictArr
{
public:
	DistrictArr(int size = 1);
	DistrictArr(istream& in); //load
	DistrictArr(const DistrictArr& origin) = delete;
	~DistrictArr();
	
	/*Getters:*/
	int getLogSize() const;
	const District& getDistrict(int district_num) const;
	const Citizen* getCitizen(int id, int district_num = -1)const;

	/*Adders:*/
	District* addDistrict(myString& name, int district_id, int electors, DistrictType type);
	int addCitizen(myString& name, int id, int birthyear, int district_id);
	void addParty(const Party* partynum);
	int addVote(int party_num, int id);
	int addRep(int party_num, int id, int district_id);

	/*Setters: */
	void changeSize(int size);

	/*Files: */
	void saveDistricts(ostream& out)const;
	void saveVotes(ostream& out)const;
	void load(istream& in);
	void link(istream& in, const PartyArr& party_map);

	void printDistricts() const;

	/*Operators: */
	District& operator[](int i) { return *district_arr[i]; }
	const District& operator[](int i) const { return *district_arr[i]; }
	friend ostream& operator<<(ostream& os, const DistrictArr& arr);
	
private:
	void doubleSize();
	DistrictPtr* district_arr;
	int log_size;
	int real_size;
};
