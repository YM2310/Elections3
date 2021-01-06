#include "DistrictPtr.h"

DistrictPtr::DistrictPtr()
{
	ptr = nullptr;
}

DistrictPtr::~DistrictPtr()
{
	delete ptr;
}
void DistrictPtr::deleteDistrict() {
	delete ptr;
	ptr = nullptr;
}
void DistrictPtr::setPtr(District* district)
{
	ptr = district;
}
