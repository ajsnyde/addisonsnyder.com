#include "iostream"
#include "Car.h"
#include "string"

using namespace std;

///////////////////////////////////////////////////////////////
//	Constructor - Sets values to a default.. (no return, no parameters)
///////////////////////////////////////////////////////////////
Car::Car()
{
	cout << "Creating a DEFAULT vehicle\n";
	delivery = 0;
	year = 2007;
	value = 9200;
	gascap = 9.2;
}

Car::Car(string test)
{
	cout << test;
}

Car::Car(double g, int y, int v, bool d, Car* c)
{
	gascap = g;
	year = y;
	value = v;
	delivery = d;
	next = c;
}


///////////////////////////////////////////////////////////////
//	Function Name - Display
//	No parameters, void return.
///////////////////////////////////////////////////////////////

void Car::display() const
{
	cout << "Displaying all vehicle attributes:\n";
	cout << "----------------------------------------\n";
	cout << "Delivery? (1 = yes, 0 = no) - " << delivery << "\n";
	cout << "Year                        - " << year << "\n";
	cout << "Value (in USD)              - " << value << "\n";
	cout << "Gas Tank Capacity           - " << gascap << "\n";
	cout << "----------------------------------------\n";
}

///////////////////////////////////////////////////////////////
//	Function Name - Returns Gas tank cap
//	No parameters, double return.
///////////////////////////////////////////////////////////////

double Car::getgascap() const
{
	return gascap;
}

///////////////////////////////////////////////////////////////
//	Function Name - Sets gas
//	Gas parameter, no return.
///////////////////////////////////////////////////////////////

void Car::setgascap(double g)
{
	gascap = g;
}

///////////////////////////////////////////////////////////////
//	Function Name - Returns value of stored car
//	No parameters, int return.
///////////////////////////////////////////////////////////////

int Car::getvalue() const
{
	return value;
}

///////////////////////////////////////////////////////////////
//	Function Name - sets value
//	Value is parameter, no return.
///////////////////////////////////////////////////////////////

void Car::setvalue(int v)
{
	value = v;
}

///////////////////////////////////////////////////////////////
//	Function Name - Returns Year
//	No parameters, int return.
///////////////////////////////////////////////////////////////

int Car::getyear() const
{
	return year;
}

///////////////////////////////////////////////////////////////
//	Function Name - sets year
//	year (int) parameter, no return.
///////////////////////////////////////////////////////////////

void Car::setyear(int y)
{
	year = y;
}

///////////////////////////////////////////////////////////////
//	Function Name - Returns delivery bool
//	No parameters, Bool return.
///////////////////////////////////////////////////////////////

bool Car::getdelivery() const
{
	return delivery;
}

///////////////////////////////////////////////////////////////
//	Function Name - Sets delivery status
//	bool parameter, no return.
///////////////////////////////////////////////////////////////

void Car::setdelivery(bool d)
{
	delivery = d;
}

void Car::setcar(Car* c)
{
	next = c;
}

Car* Car::getcar() const
{
	return next;
}