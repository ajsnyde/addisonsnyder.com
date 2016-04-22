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

class Car {
	private://variables
	bool delivery;
	int year;
	int value;
	double gascap;

	public:
	Car(); // constructor!
	Car(string);//overloaded constructor
	void display() const;//displays all attributes
	//getters
	int getvalue() const;
	int getyear() const;
	bool getdelivery() const;
	double getgascap() const;
	//setters
	void setgascap(double);
	void setyear(int);
	void setvalue(int);
	void setdelivery(bool);
};

#endif // !CAR_H