#pragma once
#include "Party.h"
class Party;
class PartyPtr
{
public:
	PartyPtr();
	PartyPtr(Party* p);
	~PartyPtr();
	void setPtr(Party* new_ptr);
	void deleteParty();
	Party* operator->() { return ptr; }
	Party& operator*() { return *ptr; }
	void operator=(const PartyPtr& other);
private:
	Party* ptr;
};
