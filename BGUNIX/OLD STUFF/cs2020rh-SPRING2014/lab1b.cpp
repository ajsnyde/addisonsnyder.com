// All code by Addison Snyder
// Calories burned program


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double calories[5];
	int counter = 0;


	cout << "Minutes:  |  Calories Burned:\n";

	while(counter != 5)
	{
		calories[counter] = (counter + 2) * (5 * 3.9);
		

		cout << right << setw(6) << ((counter + 2) * 5) << "    |  " << setprecision(1) << fixed << right << calories[counter] << "\n";
		counter++;
	}
	cin >> counter;
	return 0;
}