#pragma once
#include "SimpleElection.h"
#include "RegularElection.h"

Election* loadMenu();
string dateInput();
void mainMenu(Election* elections);// the second menu
int preMenu(); // the first menu- for load or create new
int getChoice();
void superSwitch(int choice, Election* elections);
void addDistrict(Election* elections);
void addCitizen(Election* elections);
void addParty(Election* elections);
void addRep(Election* elections);
void printDistricts(Election* elections);
void printCitizens(Election* elections);
void printParties(Election* elections);
void vote(Election* elections);
void results(Election* elections);
void saveElections(const Election& elections);
Election* loadElections(Election* elections = nullptr);
void checkDate(const string& date);
