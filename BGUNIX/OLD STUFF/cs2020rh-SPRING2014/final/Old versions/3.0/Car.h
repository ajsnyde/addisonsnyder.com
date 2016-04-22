///////////////////////////////////////////////////////////////
// FILE NAME:		Car.h
// TITLE:			Car Header File
// PROGRAMMER:  	Addison Snyder
// FOR COURSE:    	CS 2020
// DUE DATE:      	4/21/2014
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H
#include "string"
using namespace std;

class Car 
{
	friend class List;
private:
	//OFFICIAL ORDER IN WHICH PARAMETERS ARE USED:
	string make;
	string model;
	string color;	//Remain consistent in naming colors. Either use legitimate manufacturer's name (Metallic Tungsten), or stick with basic (Grey).
	string VIN;		//Vehicle Identification Number (not really a number, but a series of numbers and letters)
	string tag;		//Usually 6 char. string, i.e. 4C0023 (0023 designates #, 4C describes type)
	int year;
	int mileage;
	int value;		//MSRP if new, est. market value if used
	bool NEW;		//If car has not been owned domestically, it is new (1). This includes transferred vehicles and dealer sales. Must have original window stickers, etc.

	Car *next;
public:
	Car();
	Car(string, string, string, string, string, int, int, int, bool);
	Car(string, string, string, string, string, int, int, int, bool, Car*);
};

#endif