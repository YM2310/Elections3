#pragma once
#include "PartyPtr.h"
#include "DynamicArray.h"
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

	void changeSize(int size);

	/*Adders: */
	Party* addParty(myString& partyName, int _partyNum, const Citizen* leader);//adds new party to arr.
	void addDistrict(District* district_id);
	int addRep(int party_num, int district_num, const Citizen* newrep);
	void addElectoralVotes(int party_num, int  electors);
	void addVotes(int party_num, int votes);

	int CheckIfRep(const Citizen* newrep) const;
	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, DistrictArr& district_map);

	/*Operators*/
	friend ostream& operator<<(ostream& os, const PartyArr& arr);
	Party& operator[](int i) { return *party_arr[i]; }
	const Party& operator[](int i)const { return  party_arr[i]; }


	/*Compares*/
	class CmpElectors {
	public:
		bool operator()(const Party& party_1, const Party& party_2) {
			if (party_1.getElectorsWon() > party_2.getElectorsWon())
				return true;
			if (party_1.getElectorsWon() == party_2.getElectorsWon())
				if (party_1.getPartyNum() < party_2.getPartyNum())
					return true;
			return false;
		}
	};
	class CmpVotes {
	public:
		bool operator()(const Party& party_1, const Party& party_2) {
			if (party_1.getVotes() > party_2.getVotes())
				return true;
			if (party_1.getVotes() == party_2.getVotes())
				if (party_1.getPartyNum() < party_2.getPartyNum())
					return true;
			return false;
		}
	};

	class CmpVotes {
	public:
		bool operator()(const Party& party_1, const Party& party_2) {
			if (party_1.getElectorsWon() > party_2.getElectorsWon())
				return true;
			if (party_1.getElectorsWon() == party_2.getElectorsWon())
				if (party_1.getPartyNum() < party_2.getPartyNum())
					return true;
			return false;
		}
	};
	
private:
	DynamicArray<PartyPtr> party_arr;
	void doubleSize();
};
