///////////////////////////////////////////////////////////////
// FILE NAME: 		driver.cpp         
// TITLE:         	Test driver for List class and compatibility with Car class
// PROGRAMMER:  	Addison Snyder
// FOR COURSE:    	CS 2020
// DUE DATE:      	4/28/2014
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#include "iostream"
#include "Car.h"
#include "List.h"

using namespace std;

int main()
{

	//declaring all variables

	List Lot;
	Lot.addcar();
	Lot.addcar();
	Lot.addcar();
	cout << "Inserting car between 3rd and 4th spots. . .\n";
	Lot.insertcar(2);

	Lot.displayall();
	cout << "Getting new car's pointer and using it to change gascap to 9000. . .\n";
	(*(Lot.getcar(2))).setgascap(9000);
	Lot.displayall();
	cout << "Sending that car to the junkyard without get function.\n";
	Lot.killcar(1);
	cout << "Car should be gone!\n";
	Lot.displayall();
	return 0;
}

