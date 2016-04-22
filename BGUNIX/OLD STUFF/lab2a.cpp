//Addison Snyder
//10-2-2013

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//VARIABLES
	double tank;
	double miles;
	double mpg;

	//INPUT - asking user for tank, miles
	cout << "Please enter how many gallons your gas tank can hold: ";
	cin >> tank;
	cout << "Please enter how many miles you can drive with a full tank: ";
	cin >> miles;

	//PROCESSING: mpg
	mpg = miles / tank;
	

	//OUTPUT - display mpg
	cout << setprecision(2) << fixed << showpoint;
	cout << "You can drive " << mpg << " miles per gallon!\n";
	
	return 0;
}
