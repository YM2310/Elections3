#include "Reps.h"
class District;
class DistrictArr;
class RepsArr
{
public:
	RepsArr(int size = 1);
	~RepsArr();

	void addDistrict(const District* district_id);
	int addRep(const Citizen* rep, int district_id);
	void copyReps(Reps* origin, int origin_size);
	/*Getters: */
	int getLogSize() const;
	const Reps& getRepsOfDistrict(int district_num) const;

	/*Files: */
	void save(ostream& out) const;
	void load(istream& in, const DistrictArr& district_map);

	const Reps& operator[](int i) const { return reps[i]; }
	
private:
	Reps* reps;
	int log_size;
	int real_size;
	void doubleSize();
	void changeSize(int size);
};
