#pragma once
#include "citizenPtr.h"
#include "DynamicArray.h"
class District;
class DistrictArr;
class Reps
{
public:
	Reps(int size = 2, const District* distritct_num = nullptr); // init an empty citizenArr, according to given size
	~Reps();
	int getLogSize() const;
	int getDistrictNum() const;
	const District* getDistrict()const;
	void addCitizenToArr(const Citizen* person);
	myString getNameOfRep(int idx) const;
	int getIDRep(int idx) const;
	const DynamicArray<const Citizen*>& getAllReps() const  {
		return citizen_arr;
	}
        
	void setDistrict(const District* district);

	void save(ostream& out) const;
	void load(istream& in, const DistrictArr& district_map);
	Reps& operator=(const Reps& origin);

private:
	DynamicArray<const Citizen*> citizen_arr;
	const District* distrtict_num;
};
