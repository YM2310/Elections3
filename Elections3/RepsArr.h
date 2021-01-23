#include "Reps.h"
#include "DynamicArray.h"
class District;
class DistrictArr;
class RepsArr
{
public:
	RepsArr(int size = 2);
	~RepsArr();

	void addDistrict(const District* district_id);
	void addRep(const Citizen* rep, int district_id);
	void copyReps(Reps* origin, int origin_size);
	/*Getters: */
	int getLogSize() const;
	const Reps& getRepsOfDistrict(int district_num) const;
	const DynamicArray<Reps>& getReps() const {
		return reps;
	}

	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, const DistrictArr& district_map);

	const Reps& operator[](int i) const { return reps[i]; }
	
private:
	DynamicArray<Reps> reps;
	
};
