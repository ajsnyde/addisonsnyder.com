#include <iostream>
#include <ctime>
#include <cstlib>

using namespace std;

int main()
{
	int num;
	string choice;
	bool odd;
	
	cout << "Hi Friend!\nPlease enter a number: ";
	cin >> num;

	cout << "Even or odd?\n";
	cin >> choice;
	if ( choice == "even" )
		odd = 0;
	else
		odd = 1;
	if (num == 0)
		num += 2;
	if ( ((num % 2) == 1) && odd == 1)
		cout << "ODD NUMBER! YOU ARE CORRECT!\n";
	else if ( ((num % 2) == 0) && odd == 0)
		cout << "EVEN NUMBER! YOU ARE CORRECT!\n";
	else
		cout << "WRONG! YOU SUCK!!!\n";
	cout << "GOODBYE!";
	
	return 0;
}
