#pragma once
#include "PartyArr.h"
#include "QuickSort.h"
class Party;
struct DistrictVotes
{
	const Party* party;
	int votes;
	int reps_num;

	DistrictVotes() {
		party = nullptr;
		votes = 0;
		reps_num = 0;
	}

	DistrictVotes& operator=(const DistrictVotes& votes) {
		party = votes.party;
		this->votes = votes.votes;
		reps_num = votes.reps_num;
		return *this;
	}
};

class DistrictVotesArr
{
public:
	DistrictVotesArr(int size = 2);
	DistrictVotesArr(const DistrictVotesArr& origin);
	~DistrictVotesArr();

	/*Getters: */
	int getVotes(int party_id) const;
	int getReps(int party_id) const;
	int getLogSize() const;
	DynamicArray<DistrictVotes>::iterator begin() {
		return votes_arr.begin();
	}
	DynamicArray<DistrictVotes>::iterator end() {
		return votes_arr.end();
	}

	/*Adders: */
	void addParty(const Party* party);
	void addVote(int party_id);
	void addRep(int party_id);


	void bubbleReminder(float reps_per_vote, int reps_remaining);
	void swap(DistrictVotes* a, DistrictVotes* b);
	/*Operators: */
	DistrictVotes& operator[](int i) { return votes_arr[i]; }
	const DistrictVotes& operator[](int i) const { return votes_arr[i]; }
	DistrictVotesArr& operator=(const DistrictVotesArr& origin);

	class cmpDistrictVotes {
	public:
		bool operator()(const DistrictVotes& party_1, const DistrictVotes& party_2) const {
			if (party_1.reps_num < party_2.reps_num)
				return true;
			if (party_1.reps_num == party_2.reps_num)
				if (party_1.party->getPartyNum() < party_2.party->getPartyNum())
					return true;
			return false;
		}
	};

	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, const PartyArr& party_map);

private:
	DynamicArray<DistrictVotes> votes_arr;
};
