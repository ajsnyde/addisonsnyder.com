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
	friend class List;

	private://variables
	bool delivery;
	int year;
	int value;
	double gascap;
	Car* next;

	public:
	Car(); // constructor!
	Car(string);//overloaded constructor
	Car(double, int, int, bool, Car*); // setup value overloaded constructor
	void display() const;//displays all attributes
	//getters
	int getvalue() const;
	int getyear() const;
	bool getdelivery() const;
	double getgascap() const;
	Car* getcar() const;
	//setters
	void setgascap(double);
	void setyear(int);
	void setvalue(int);
	void setdelivery(bool);
	void setcar(Car*);
};

#endif // !CAR_H