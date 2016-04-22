//Addison Snyder
//calculates distance traveled 

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double speed = 0;
	double time = 0;
	int counter = 0;

	
	cout << "Hello! Welcome to the milage calculator!\n";
	while(speed <= 0 && time < 1)
	{
		cout << "Please enter speed: ";
		cin >> speed;
		cout << "Please enter time: ";
		cin >> time;
	}
	time++;
	cout << "Hours      Distance Traveled\n";
	cout << "----------------------------\n";			
		while (counter != time)
		{		
			cout << " " << setw(3) << counter << "      " << setw(5) << (counter * speed) << "\n";
			counter++;
		}
	return 0;
}
