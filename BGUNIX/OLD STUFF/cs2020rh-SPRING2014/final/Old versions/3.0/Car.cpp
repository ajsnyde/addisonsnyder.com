#include "iostream"
#include "Car.h"
#include "string"

using namespace std;

///////////////////////////////////////////////////////////////
//	Constructor - Sets values to a default.. (no return, no parameters)
///////////////////////////////////////////////////////////////
Car::Car()
{

}

Car::Car(string tempmake, string tempmodel, string tempcolor, string tempVIN, string temptag, int tempyear, int tempmileage, int tempvalue, bool tempNEW)
{
	make = tempmake;
	model = tempmodel;
	color = tempcolor;
	VIN = tempVIN;
	tag = temptag;
	year = tempyear;
	mileage = tempmileage;
	value = tempvalue;
	NEW = tempNEW;
}

Car::Car(string tempmake, string tempmodel, string tempcolor, string tempVIN, string temptag, int tempyear, int tempmileage, int tempvalue, bool tempNEW, Car *tempnext)
{
	make = tempmake;
	model = tempmodel;
	color = tempcolor;
	VIN = tempVIN;
	tag = temptag;
	year = tempyear;
	mileage = tempmileage;
	value = tempvalue;
	NEW = tempNEW;
	next = tempnext;
}
///////////////////////////////////////////////////////////////
//	Function Name - Display
//	No parameters, void return.
///////////////////////////////////////////////////////////////