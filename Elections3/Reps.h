#pragma once
#include "citizenPtr.h"
#include <map>

class District;
class DistrictArr;
class Reps
{
public:
	Reps(int size = 1, const District* distritct_num = nullptr); // init an empty citizenArr, according to given size
	~Reps();
	int getLogSize() const;
	int getDistrictNum() const;
	const District* getDistrict()const;
	void doubleSize();
	void changeSize(int new_size);
	int addCitizenToArr(const Citizen* person);
	string getNameOfRep(int idx) const;
	int getIDRep(int idx) const;

	void setDistrict(const District* district);

	void save(ostream& out) const;
	void load(istream& in, const DistrictArr& district_map);
	Reps& operator=(const Reps& origin);

private:
	const District* distrtict_num;
	map<int, Citizen*> citizen_arr; //int= id of citizen
	int log_size;
	int real_size;
};
