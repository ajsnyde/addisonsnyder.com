///////////////////////////////////////////////////////////////
// FILE NAME: 		driver.cpp         
// TITLE:         	Test driver for 'car' class
// PROGRAMMER:  	Addison Snyder
// FOR COURSE:    	CS 2020
// DUE DATE:      	4/21/2014
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#include "iostream"
#include "Car.h"

using namespace std;

int main()
{

	//declaring all variables
	Car Taxi;
	Car newcar("Overloaded constructor works!\n");//overloaded constructor
	int y;
	int v;
	double g;
	bool d;
	int new_value;

	//displays all values (specifically, one that were initialized in constructor)
	Taxi.display();
	//testing all member functions..
	cout << "Enter new year: ";
	cin >> y;
	Taxi.setyear(y);
	cout << "Enter new value: ";
	cin >> v;
	Taxi.setvalue(v);
	cout << "Enter new gas cap: ";
	cin >> g;
	Taxi.setgascap(g);
	cout << "Delivery? (1 = yes, 0 = no): ";
	cin >> d;
	Taxi.setdelivery(d);
	cout << "Displaying new set of data:\n";
	Taxi.display();

	cout << "Getting data from class. . .\n";//testing one of the four functions that GET data.
	new_value = Taxi.getvalue();//returns data from class
	if(new_value == Taxi.getvalue())//verifies that data is legit
		cout << "Values match! Successful Operation!\n";
	else
		cout << "Something went wrong!\n";
	return 0;
}

