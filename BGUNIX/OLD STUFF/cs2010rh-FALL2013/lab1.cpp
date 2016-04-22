////////////////////////////////////////////////////
//Project: Ticket Booth
// Programmer: Addison Snyder
//Date: 9-30-13
//Class: CS 2010 2:30 - 4:00 PM
//Description: Sell tickets to customers in
//an easy and effective manner
//ALL CODE IS MINE UNLESS OTHERWISE INDICATED
////////////////////////////////////////////////////

#include "iostream"
#include "string"
#include "iomanip"

using namespace std;

int main()
{
	//variables and constants
	const double BLEACHER_COST = 10;
	const double FIELD_COST = 40;
	const double UPPER_COST = 60;

	int bleacher;
	int field;
	int upper;

	string name;

//GREETING

	cout << "****************************************\n";
	cout << "      Welcome to Jacob’s Field!        \n";
	cout << "****************************************\n";
	cout << "We have the following tickets available:\n";
	cout << "           Bleacher  @ $" << BLEACHER_COST;
	cout << "\n           Field Box @ $" << FIELD_COST;
	cout << "\n           Upper Box @ $" << UPPER_COST;
	cout << "\n\n";
//INPUT: Take names & numbers.
	cout << "Enter your name: ";
	getline(cin, name);
	cout << "Enter number of bleacher tickets:   ";
	cin >> bleacher;
	cout << "Enter number of field tickets:      ";
	cin >> field;
	cout << "Enter number of upper tickets:      ";
	cin >> upper;
	cout << "\n\n----------------------------------------";
//OUTPUT: Show calculated totals on reciept.
	cout << "\nSales Receipt – Jacob’s Field\n";
	cout << "----------------------------------------\n";
	cout << "Customer:  " << name << "\n\n";
	cout << bleacher << " bleacher     @ $";
	cout << setprecision(2) << fixed << BLEACHER_COST;
	cout << "  = $" << setw(6) << (BLEACHER_COST * bleacher);
	cout << "\n" << field << " field        @ $";
	cout << FIELD_COST;
	cout << "  = $" << setw(6) << (FIELD_COST * field);
	cout << "\n" << upper << " uppper       @ $";
	cout << UPPER_COST;
	cout << "  = $" << setw(6) << (UPPER_COST * upper);
	cout << "\n\n";
	cout << "----------------------------------------\n";
	cout << "Total Due:                 $";
	cout <<	((UPPER_COST * upper) + (FIELD_COST * field) + (BLEACHER_COST * bleacher));
	cout << "\n----------------------------------------\n\n";
	cout << "Proceeding to checkout. . .\a\a\a\n";
	return 0;
}