#pragma once
#include "PartyPtr.h"
class District;
class PartyArr {
public:
	PartyArr(int _logsize = 0, int _realsize = 1); //init an empty partyArr
	PartyArr(const PartyArr& origin) = delete;
	PartyArr(istream& in, DistrictArr& district_map);
	~PartyArr();// delete[] -partyArr

	/*Getters: */
	Party& getParty(int partyNum) const; // returnes the Party itself for a name
	int getLogSize() const;

	/*Setters: */
	void initElectors();

	int partitionByVotes(PartyArr& arr, int left, int right);
	void changeSize(int size);
	void quickSortByVotes(PartyArr& arr, int left, int right);

	/*Adders: */
	Party* addParty(myString& partyName, int _partyNum, const Citizen* leader);//adds new party to arr.
	void addDistrict(District* district_id);
	int addRep(int party_num, int district_num, const Citizen* newrep);
	void addElectoralVotes(int party_num, int  electors);
	void addVotes(int party_num, int votes);

	int CheckIfRep(const Citizen* newrep) const;
	void quickSort(PartyArr& arr, int left, int right);

	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, DistrictArr& district_map);

	/*Operators*/
	friend ostream& operator<<(ostream& os, const PartyArr& arr);
	Party& operator[](int i) { return *party_arr[i]; }
	const Party& operator[](int i)const { return  *party_arr[i]; }
	
private:
	int log_size;
	int real_size;
	PartyPtr* party_arr;
	void doubleSize();
	int partition(PartyArr& arr, int left, int right);
};
