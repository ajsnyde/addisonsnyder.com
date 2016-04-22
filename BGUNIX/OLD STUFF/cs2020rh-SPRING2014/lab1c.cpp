// All code made by Addison Snyder
// Celsius to Fahrenheit
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double celsius;
	cout << "Celsius  |  Fahrenheit\n";
	cout << "---------+------------\n";
	for(int i = 0; i != 21; i++)
	{
		celsius = i;
		cout << setw(7) << right << i  << "  |  ";
		cout << setprecision(1) << fixed << (celsius*(1.8)) + 32 << "\n";
	}
	return 0;
}