#pragma once
#include "PartyArr.h"
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
	DistrictVotesArr(int size = 1);
	DistrictVotesArr(const DistrictVotesArr& origin);
	~DistrictVotesArr();

	/*Getters: */
	int getVotes(int party_id) const;
	int getReps(int party_id) const;
	int getLogSize() const;

	/*Adders: */
	void addParty(const Party* party);
	void addVote(int party_id);
	void addRep(int party_id);


	void bubbleReminder(float reps_per_vote, int reps_remaining);
	void qSort();

	/*Operators: */
	DistrictVotes& operator[](int i) { return votes_arr[i]; }
	const DistrictVotes& operator[](int i) const { return votes_arr[i]; }
	DistrictVotesArr& operator=(const DistrictVotesArr& origin);

	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, const PartyArr& party_map);

private:
	void changeSize(int size);
	void doubleSize();
	int partition(DistrictVotes* arr, int low, int high);
	void quickSort(DistrictVotes* arr, int low, int high);
	void swap(DistrictVotes* a, DistrictVotes* b);
	DistrictVotes* votes_arr;
	int log_size;
	int real_size;
};
