#include "RepsArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

RepsArr::RepsArr(int size) : reps(size)
{
}

RepsArr::~RepsArr()
{
}

void RepsArr::addDistrict(const District* district_id)
{
	reps.push_back(Reps(1, district_id));
}

int RepsArr::addRep(const Citizen* rep, int district_id)
{
	for (auto& reps_of_dist : reps) {
		if (reps_of_dist.getDistrictNum() == district_id) {
			reps_of_dist.addCitizenToArr(rep);
			return 200; //validates OK
		}
	}
	return 400; // not found this district
}

void RepsArr::copyReps(Reps* origin, int origin_size) {
	reps.clear();
	for (int i = 0; i < origin_size; i++)
	{
		reps.push_back(origin[i]);
	}
}


int RepsArr::getLogSize() const
{
	return reps.size();
}

const Reps& RepsArr::getRepsOfDistrict(int district_num) const
{
	for (int i = 0; i < reps.size(); i++)
	{
		if (reps[i].getDistrictNum() == district_num) {
			return reps[i];
		}
	}

}

void RepsArr::save(ostream& out) const
{
	int log_size = reps.size();
	out.write(rcastcc(&log_size), sizeof(int));
	for (int i = 0; i < log_size; i++)
	{
		reps[i].save(out);
	}
}

void RepsArr::load(istream& in, const DistrictArr& district_map)
{
	int reps_arr_size;
	in.read(rcastc(&reps_arr_size), sizeof(int));

	for (int i = 0; i < reps_arr_size; i++)
	{
		Reps temp;
		temp.load(in, district_map);
		reps.push_back(temp);
	}
}

