//Addison Snyder
//10-2-13
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//VARIABLES & CONSTANTS
	const double YEN_PER_DOLLAR = 83.14;
	const double EUROS_PER_DOLLAR = .7337;
	double dollars;
	double yen;
	double euros;

	//INPUT - find # to convert
	cout << "Please enter the # of dollars: ";
	cin >> dollars;
	
	//PROCESSING - multiply #s
	yen = YEN_PER_DOLLAR * dollars;
	euros = EUROS_PER_DOLLAR * dollars;

	//OUTPUT
	cout << setprecision(2) << showpoint << fixed;
	cout << "You have " << yen << " yen!\n";
	cout << "You have " << euros << " euros!\n";

return 0;
}

