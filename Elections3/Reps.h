#pragma once
#include "citizenPtr.h"

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
	myString getNameOfRep(int idx) const;
	int getIDRep(int idx) const;
        
	void setDistrict(const District* district);

	void save(ostream& out) const;
	void load(istream& in, const DistrictArr& district_map);

	const Citizen& operator[](int i)const { return *citizen_arr[i]; }
	Reps& operator=(const Reps& origin);
	
private:
	const District* distrtict_num;
	const Citizen** citizen_arr;
	int log_size;
	int real_size;
};
