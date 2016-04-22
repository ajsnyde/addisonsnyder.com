// All code made by Addison Snyder
// ASCII Char Program

#include <iostream>

using namespace std;

int main()
{
	char letter = 0;
	while(letter != 127)
	{
		cout << letter;
		letter++;
		if(letter % 16 == 0)
			cout << "\n";
	}
	cin >> letter;
	return 0;
}

