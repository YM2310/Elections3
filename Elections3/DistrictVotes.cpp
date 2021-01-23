#include "DistrictVotes.h"
#include <iostream>
#include "PartyArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class PartyArr;
DistrictVotesArr::DistrictVotesArr(int size)
{
	log_size = 0;
	real_size = size;
	votes_arr = new DistrictVotes[real_size];
}

DistrictVotesArr::DistrictVotesArr(const DistrictVotesArr& origin)
{
	try {
		log_size = origin.log_size;
		real_size = origin.real_size;
		votes_arr = new DistrictVotes[real_size];

		for (int i = 0; i < log_size; i++)
		{
			votes_arr[i] = origin.votes_arr[i];
		}
	}
	catch (bad_alloc& ex) {
		throw;
	}
}

DistrictVotesArr::~DistrictVotesArr()
{
	delete[] votes_arr;
}

void DistrictVotesArr::addParty(const Party* party_id)
{
	if (log_size == real_size) {
		doubleSize();
	}
	votes_arr[log_size].party = party_id;
	log_size++;
}

void DistrictVotesArr::addVote(int party_id)
{
	for (int i = 0; i < log_size; i++)
	{
		if (votes_arr[i].party->getPartyNum() == party_id) {
			votes_arr[i].votes++;
			return;
		}
	}
	throw "No party with this id";
}

void DistrictVotesArr::addRep(int party_id)
{
	for (int i = 0; i < log_size; i++)
	{
		if (votes_arr[i].party->getPartyNum() == party_id) {
			votes_arr[i].reps_num++;
			return;
		}
	}
	throw "no party with this id";
}

void DistrictVotesArr::changeSize(int size)
{
	try {
		real_size = size;
		DistrictVotes* new_arr = new DistrictVotes[real_size];
		std::memcpy(new_arr, votes_arr, log_size * sizeof(DistrictVotes));
		delete[]votes_arr;
		votes_arr = new_arr;
	}
	catch (bad_alloc& ex) {
		throw;
	}
}


float myfmod(float x, float y) {
	return x - (static_cast<int>(x / y) * y);
}

void DistrictVotesArr::bubbleReminder(float reps_per_vote, int reps_remaining)
{
	int j = 0;
	int i = 0;
	for (i = 0; i < reps_remaining; i++) {
		for (j = 0; j < log_size - i - 1; j++) {
			if (myfmod(votes_arr[j].votes, reps_per_vote) <= myfmod(votes_arr[j + 1].votes, reps_per_vote))
				swap(&votes_arr[j], &votes_arr[j + 1]);
			if (myfmod(votes_arr[j].votes, reps_per_vote) == myfmod(votes_arr[j + 1].votes, reps_per_vote)) {
				if (votes_arr[j].party->getPartyNum() < votes_arr[j + 1].party->getPartyNum())
					swap(&votes_arr[j], &votes_arr[j + 1]);
			}
		}
	}
}

void DistrictVotesArr::swap(DistrictVotes* a, DistrictVotes* b) {
	DistrictVotes temp = *a;
	*a = *b;
	*b = temp;
}

int DistrictVotesArr::getVotes(int party_id) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (votes_arr[i].party->getPartyNum() == party_id) {
			return votes_arr[i].votes;
		}
	}
}

int DistrictVotesArr::getReps(int party_id) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (votes_arr[i].party->getPartyNum() == party_id) {
			return votes_arr[i].reps_num;
		}
	}
}

int DistrictVotesArr::getLogSize() const
{
	return log_size;
}

void DistrictVotesArr::save(ostream& out) const
{
	try {
		out.write(rcastcc(&log_size), sizeof(log_size));
		for (int i = 0; i < log_size; i++)
		{
			int party_num = votes_arr[i].party->getPartyNum();
			out.write(rcastcc(&party_num), sizeof(party_num));
			out.write(rcastcc(&votes_arr[i].votes), sizeof(int));
			out.write(rcastcc(&votes_arr[i].reps_num), sizeof(int));
		}
	}
	catch (ostream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void DistrictVotesArr::load(istream& in, const PartyArr& party_map) {
	try {
		int votes_arr_size;
		in.read(rcastc(&votes_arr_size), sizeof(int));
		changeSize(votes_arr_size + 1);
		log_size = votes_arr_size;
		int party_id;
		for (int i = 0; i < log_size; i++)
		{
			in.read(rcastc(&party_id), sizeof(int));
			votes_arr[i].party = &party_map.getParty(party_id);
			in.read(rcastc(&votes_arr[i].votes), sizeof(votes_arr[i].votes));
			in.read(rcastc(&votes_arr[i].reps_num), sizeof(votes_arr[i].reps_num));
		}
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

void DistrictVotesArr::doubleSize()
{
	changeSize(real_size * 2);
}

int DistrictVotesArr::partition(DistrictVotes* arr, int low, int high)
{
	DistrictVotes pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j].reps_num > pivot.reps_num)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
		if (arr[j].reps_num == pivot.reps_num) {
			if (arr[j].party->getPartyNum() < pivot.party->getPartyNum()) {
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]);
			}
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void DistrictVotesArr::qSort()
{
	quickSort(votes_arr, 0, log_size - 1);
}

DistrictVotesArr& DistrictVotesArr::operator=(const DistrictVotesArr& origin)
{
	log_size = origin.log_size;
	real_size = origin.real_size;
	votes_arr = new DistrictVotes[real_size];

	for (int i = 0; i < log_size; i++)
	{
		votes_arr[i] = origin.votes_arr[i];
	}
	return *this;
}

void DistrictVotesArr::quickSort(DistrictVotes* arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
