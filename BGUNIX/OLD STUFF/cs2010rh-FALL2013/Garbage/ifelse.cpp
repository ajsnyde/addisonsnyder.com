//practice if/else statements

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
	int num;
	
	cout << "Enter a number: ";
	cin >> num;
	if (num > 0)
	cout << "POSTITIVE...\n\n";
	else if (num == 0)
	cout << "ZERO!!!!\n\n";
	else
	cout << "NEGATIVE\n\n";

	return 0;
}

