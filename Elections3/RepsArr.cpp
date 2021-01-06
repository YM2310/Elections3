#include "RepsArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

RepsArr::RepsArr(int size)
{
	log_size = 0;
	real_size = size;
	reps = new Reps[real_size];
}

RepsArr::~RepsArr()
{
	delete[] reps;
}

void RepsArr::addDistrict(const District* district_id)
{
	if (log_size == real_size)
		doubleSize();
	reps[log_size] = Reps(1, district_id);
	log_size++;
}

int RepsArr::addRep(const Citizen* rep, int district_id)
{
	for (int i = 0; i < log_size; i++) {
		if (reps[i].getDistrictNum() == district_id) {
			reps[i].addCitizenToArr(rep);
			return 200; //validates OK
		}
	}
	return 400; // not found this district
}

void RepsArr::copyReps(Reps* origin, int origin_size) {
	log_size = origin_size;
	real_size = origin_size+1;
	reps = new Reps[real_size];
	for (int i = 0; i < origin_size; i++)
	{
		reps[i] = origin[i];
	}
}

void RepsArr::doubleSize() {
	changeSize(real_size * 2);
}

void RepsArr::changeSize(int size)
{
	real_size = size;
	Reps* new_size = new Reps[real_size];
	for (int i = 0; i < log_size; i++)
	{
		new_size[i] = reps[i];
	}
	delete[] reps;
	reps = new_size;
}

int RepsArr::getLogSize() const
{
	return log_size;
}

const Reps& RepsArr::getRepsOfDistrict(int district_num) const
{
	for (int i = 0; i < log_size; i++)
	{
		if (reps[i].getDistrictNum() == district_num) {
			return reps[i];
		}
	}

}

void RepsArr::save(ostream& out) const
{
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
	changeSize(reps_arr_size+1);
	log_size = reps_arr_size;
	for (int i = 0; i < log_size; i++)
	{
		reps[i].load(in, district_map);
	}
}

