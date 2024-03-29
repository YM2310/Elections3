#include "Menu.h"
#include <iostream>
#include <fstream>
#include "myString.h"
#include <typeinfo>
using namespace std;
enum class ElectionType { REGULAR = 1, SIMPLE = 2 };
enum choice { district = 1, citizen = 2, party = 3, rep = 4, disp_districts = 5, disp_citizens = 6, disp_partys = 7, set_vote = 8, disp_results = 9, save = 11, load = 12 };

int preMenu() //The first menu- first we ask if the use wants to load / create new one
{
	Election* elections=nullptr;
	int day, month, year;
	int choice = 0;
	while (choice != 1 && choice != 2) {
		cout << "***********************************" << endl <<
			"Please Enter: " << endl <<
			"1- Create new election" << endl <<
			"2- load election" << endl;
		cin >> choice;
		cin.ignore();
		if (choice != 1 && choice != 2) {
			cout << "Ilegal input" << endl;
		}

	}
	if (choice == 1) { //New Election
		cout << "please enter date: " << endl;
		cin >> day >> month >> year;
		myString date = itos(day) + "/" + itos(month) + "/" + itos(year);

		do {
			cout << "Please enter the type of election:" << endl <<
				"1- Regular Election" << endl << "2- Simple Election" << endl;
			cin >> choice;
			if (choice != 1 && choice != 2) {
				cout << "Ilegal input" << endl;
			}
		} while (choice != 1 && choice != 2);


		if (choice == 1)
		{
			elections = new RegularElection(date);
		}
		else if (choice == 2)
		{
			cout << "Enter number of electors: " << endl;
			int electors;
			cin >> electors;
			elections = new SimpleElection(date, electors);
		}
	}
	else if (choice == 2) {  //Load election
		elections= loadElections();
	}
	mainMenu(elections);
	return 1;
}


myString dateInput() {
	myString date;
	cout << "Please enter date of election (format: dd/mm/yyyy ): " << endl;
	cin >> date;
	while (!checkDate(date)) { //checkes if the date is at the right format
		cout << "Not a valid date. Please enter date of election (format: dd/mm/yyyy ): " << endl;
		cin >> date;
	}
	return date;
}

void mainMenu(Election* elections)
{
	int choice = 100;
	while (choice != 10) {
		cout << "***********************************" << endl <<
			"Please Enter: " << endl <<
			"1- To add a district" << endl <<
			"2- To add a citizen" << endl <<
			"3- To add a party" << endl <<
			"4- To add a citizen as a representative" << endl <<
			"5- To display all districts" << endl <<
			"6- To display all citizens" << endl <<
			"7- To display all partys" << endl <<
			"8- Vote" << endl <<
			"9- To display the results of the election" << endl <<
			"10- Exit" << endl <<
			"11- Save elections" << endl <<
			"12- Load elections" << endl <<
			"***********************************" << endl;
		choice = getChoice();
		if (choice == load)
			elections = loadElections(elections);
		else
			superSwitch(choice, elections);
	}
	cout << "Goodbye!";
}

int getChoice() {
	cout << "Please enter number according to the main list above: " << endl;
	int choice;
	cin >> choice;
	while (choice > 12 || choice < 1) {
		cout << "invalid input; please enter a number between 1-12" << endl;
		cin >> choice;
	}
	cin.ignore();
	return choice;
}

void superSwitch(int choice, Election* elections) {
	switch (choice)
	{
	case district: {
		if (typeid(*elections) == typeid(SimpleElection)) {
			cout << "Simple elections, cant add district" << endl;
			break;
		}
		addDistrict(elections);
		break;
	}
	case citizen: {addCitizen(elections); break; }
	case party: {addParty(elections); break; }
	case rep: {addRep(elections); break; }
	case disp_districts: {printDistricts(elections); break; }
	case disp_citizens: {printCitizens(elections); break; }
	case disp_partys: {printParties(elections); break; }
	case set_vote: {vote(elections);  break; }
	case disp_results: {results(elections); break; }
	case save: {saveElections(*elections); break; }
	default:
		break;
	}
}

void addDistrict(Election* elections) { //add District- only to Regular Election!
	myString name;
	int num_of_reps = 0, type;
	cout << "Please enter district's name: " << endl;
	cin >> name;
	cout << "Please enter number of representatives: " << endl;
	cin >> num_of_reps;
	cout << "Please enter type of disrict: Winner Takes All District= 1, Relative District= 2" << endl;
	cin >> type;
	while (num_of_reps < 1) {
		cout << "Cant have negative number of representatives! try again. " << endl;
		cin >> num_of_reps;
	}
	int res = static_cast<RegularElection*>(elections)->addDistrict(name, num_of_reps, static_cast<DistrictType> (type));

	if (res == 200)
		cout << "Added District" << endl;
	else
		cout << "District already exist!" << endl;
}
void addCitizen(Election* elections) {
	myString name;
	int id, birth_year, district_num, res;
	cout << "Please enter name: " << endl;
	cin >> name;
	cout << "Please enter id: " << endl;
	cin >> id;
	cout << "Please enter year of birth (yyyy): " << endl;
	cin >> birth_year;
	cout << "Please enter  number of district: " << endl;
	cin >> district_num;
	res = elections->addCitizen(name, id, birth_year, district_num);

	if (res == 200)
		cout << "Added citizen" << endl;
	if (res == 400)
		cout << "No District with this number!" << endl;
	if (res == 100)
		cout << "Citizen already exist!" << endl;
}

void addParty(Election* elections) {
	myString name;
	int id_pres, res;
	cout << "Please enter name of party: " << endl;
	cin >> name;
	cout << "Please enter id of running to presidency: " << endl;
	cin >> id_pres;
	res = elections->addParty(name, id_pres);

	if (res == 400)
		cout << "No Citizen with this ID!" << endl;
	if (res == 100)
		cout << "This person is already a representative" << endl;
	if (res == 200)
		cout << "Party added" << endl;;
}

void addRep(Election* elections) {
	int rep_id, party_num, district_num, res;
	cout << "Please enter id of representative: " << endl;
	cin >> rep_id;
	cout << "Please enter number of party: " << endl;
	cin >> party_num;
	cout << "Please enter number of district: " << endl;
	cin >> district_num;
	if (typeid(*elections) == typeid(RegularElection))
	{
		if (!(static_cast<RegularElection*>(elections)->checkDistrictExists(district_num))) {
			cout << "District not found" << endl;
			return;
		}
	}
	if (!(elections->checkPartyExists(party_num))) {
		cout << "Party not found" << endl;
		return;
	}
	res = elections->addRep(party_num, rep_id, district_num);

	if (res == 200)
		cout << "Rep Added" << endl;
	else if (res == 400)
		cout << "Citizen not found" << endl;
	else
		cout << "This citizen is already a representative" << endl;
}

void printDistricts(Election* elections) { //Print districts- only to Regular Election
	if (typeid(*elections) == typeid(RegularElection))
		static_cast<RegularElection*>(elections)->printDistricts();
	else
		cout << "Cant print districts in simple election" << endl;
}

void printCitizens(Election* elections) {
	elections->printCitizens();
}
void printParties(Election* elections) {
	cout << elections->getPartyArr();
}
void vote(Election* elections) {
	int id, party_num, res;
	cout << "Please enter id of voter: " << endl;
	cin >> id;
	cout << "Please enter number of party chosen: " << endl;
	cin >> party_num;
	if (!(elections->checkPartyExists(party_num))) {
		cout << "Party not found" << endl;
		return;
	}
	res= elections->addVote(id, party_num);

	if (res == 200)
		cout << "Vote added" << endl;
	else if (res == 100)
		cout << "This citizen has already voted" << endl;
	else
		cout << "Could not find the citizen" << endl;
}
void results(Election* elections) {
	if (elections->getPartyArr().getLogSize() == 0) {
		cout << "No Parties exist yet!" << endl;
		return;
	}
	if (typeid(elections) == typeid(RegularElection)) {
		if (static_cast<RegularElection*>(elections)->getDistrictArr().getLogSize() == 0) {
			cout << "No Districts exist yet!" << endl;
			return;
		}
	}
	cout <<"The date of the election is: "<< elections->getDate() << endl;
	elections->sumElectors();
	if (elections->checkReps())
		elections->printResults(cout);
	else
		cout << "Not enough representatives!" << endl;
}

void saveElections(const Election& elections) {
	myString name;
	cout << "Please enter filename" << endl;
	cin >> name;
	ofstream outfile(&name[0], ios::binary);
	if (typeid(elections) == typeid(SimpleElection)) {
		ElectionType type = ElectionType::SIMPLE;
		outfile.write(rcastcc(&type), sizeof(ElectionType::SIMPLE));
	}
	else if (typeid(elections) == typeid(RegularElection)) {
		ElectionType type = ElectionType::REGULAR;
		outfile.write(rcastcc(&type), sizeof(ElectionType::REGULAR));
	}
	elections.save(outfile);
	outfile.close();
}

Election* loadElections(Election* election) {
	myString name;
	cout << "enter filename" << endl;
	cin >> name;
	ifstream infile(&name[0], ios::binary);
	delete election;
	ElectionType type;
	Election* new_elections = nullptr;
	infile.read(rcastc(&type), sizeof(type));
	if (type == ElectionType::REGULAR) {
		new_elections = new RegularElection(infile);

	}
	else if (type == ElectionType::SIMPLE) {
		new_elections = new SimpleElection(infile);
	}
	infile.close();
	return new_elections;
}

bool checkDate(const myString& date)
{
	if (date[2] != '/' || date[5] != '/')
		return false;
	int day1 = date[0] - '0', day2 = date[1] - '0';
	int day = day1 * 10 + day2;
	int mo1 = date[3] - '0', mo2 = date[4] - '0';
	int mo = mo1 * 10 + mo2;
	int y1 = date[6] - '0', y2 = date[7] - '0', y3 = date[8] - '0', y4 = date[9] - '0';
	int year = y1 * 1000 + y2 * 100 + y3 * 10 + y4;
	if (0 < day < 32 && 0 < mo < 13 && 0 < year < 9999)
		return true;
	else
		return false;
}
