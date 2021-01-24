#include "DistrictVotes.h"
#include <iostream>
#include "PartyArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class PartyArr;
DistrictVotesArr::DistrictVotesArr(int size) : votes_arr(size)
{
}

DistrictVotesArr::DistrictVotesArr(const DistrictVotesArr& origin) : votes_arr(origin.getLogSize())
{
	try {
		for (int i = 0; i < origin.getLogSize(); i++)
		{
			votes_arr.push_back(origin.votes_arr[i]);
		}
	}
	catch (bad_alloc& ex) {
		throw ex;
	}
}

DistrictVotesArr::~DistrictVotesArr()
{
}

void DistrictVotesArr::addParty(const Party* party_id)
{
	DistrictVotes votes;
	votes.party = party_id;
	votes_arr.push_back(votes);
}

void DistrictVotesArr::addVote(int party_id)
{
	for (auto& votes : votes_arr)
	{
		if (votes.party->getPartyNum() == party_id) {
			votes.votes++;
			return;
		}
	}
	throw invalid_argument("No party with this id");
}

void DistrictVotesArr::addRep(int party_id)
{
	for (auto& votes : votes_arr)
	{
		if (votes.party->getPartyNum() == party_id) {
			votes.reps_num++;
			return;
		}
	}
	throw invalid_argument("no party with this id");
}

float myfmod(float x, float y) {
	return x - (static_cast<int>(x / y) * y);
}

void DistrictVotesArr::bubbleReminder(float reps_per_vote, int reps_remaining)
{
	int j = 0;
	int i = 0;
	for (i = 0; i < reps_remaining; i++) {
		for (j = 0; j < votes_arr.size() - i - 1; j++) {
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
	for (auto& votes : votes_arr)
	{
		if (votes.party->getPartyNum() == party_id) {
			return votes.votes;
		}
	}
	throw invalid_argument("No party with this id");
}

int DistrictVotesArr::getReps(int party_id) const
{
	for (auto& votes : votes_arr)
	{
		if (votes.party->getPartyNum() == party_id) {
			return votes.reps_num;
		}
	}
}

int DistrictVotesArr::getLogSize() const
{
	return votes_arr.size();
}

void DistrictVotesArr::save(ostream& out) const
{
	try {
		int log_size = votes_arr.size();
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
		int party_id;
		for (int i = 0; i < votes_arr_size; i++)
		{
			DistrictVotes temp;

			in.read(rcastc(&party_id), sizeof(int));
			in.read(rcastc(&temp.votes), sizeof(votes_arr[i].votes));
			in.read(rcastc(&temp.reps_num), sizeof(votes_arr[i].reps_num));
			temp.party = &party_map.getParty(party_id);

			votes_arr.push_back(temp);
		}
	}
	catch (istream::failure& ex) {
		throw("Exception opening/reading/closing file");
	}
}

//int DistrictVotesArr::partition(DistrictVotes* arr, int low, int high)
//{
//	DistrictVotes pivot = arr[high];    // pivot 
//	int i = (low - 1);  // Index of smaller element 
//
//	for (int j = low; j <= high - 1; j++)
//	{
//		// If current element is smaller than or 
//		// equal to pivot 
//		if (arr[j].reps_num > pivot.reps_num)
//		{
//			i++;    // increment index of smaller element 
//			swap(&arr[i], &arr[j]);
//		}
//		if (arr[j].reps_num == pivot.reps_num) {
//			if (arr[j].party->getPartyNum() < pivot.party->getPartyNum()) {
//				i++;    // increment index of smaller element 
//				swap(&arr[i], &arr[j]);
//			}
//		}
//	}
//	swap(&arr[i + 1], &arr[high]);
//	return (i + 1);
//}

//void DistrictVotesArr::qSort()
//{
//	quickSort(votes_arr, 0, log_size - 1);
//}

DistrictVotesArr& DistrictVotesArr::operator=(const DistrictVotesArr& origin)
{
	votes_arr.clear();
	for (int i = 0; i < origin.getLogSize(); i++)
	{
		votes_arr.push_back(origin.votes_arr[i]);
	}
	return *this;
}
//
//void DistrictVotesArr::quickSort(DistrictVotes* arr, int low, int high)
//{
//	if (low < high)
//	{
//		int pi = partition(arr, low, high);
//		quickSort(arr, low, pi - 1);
//		quickSort(arr, pi + 1, high);
//	}
//}
