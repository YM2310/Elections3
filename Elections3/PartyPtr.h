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
	const Party* operator->()const { return ptr; }
	const Party& operator*() const { return *ptr; }
	void operator=(const PartyPtr& other);
	void operator=(Party* other);
private:
	Party* ptr;
};
