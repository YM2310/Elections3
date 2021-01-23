#pragma once
#include "Citizen.h"

class CitizenPtr {
public:
	CitizenPtr();
	~CitizenPtr();
	CitizenPtr(string _name, int _id, int _birth_year, District* _district, bool _voted = false);
	CitizenPtr(const CitizenPtr&) = delete;
	CitizenPtr(Citizen* p) : ptr(p) {}

	/*Getters: */
	Citizen* getAddress();
	bool isNull();

	/*Setters: */
	bool setPtr(Citizen* citizen);
	void deleteCitizen();

	/*Operators: */
	Citizen* operator->() { return ptr; }
	Citizen& operator*() { return *ptr; }

private:
	Citizen* ptr;
};
