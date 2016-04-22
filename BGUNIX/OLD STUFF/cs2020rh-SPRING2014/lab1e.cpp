// All code by Addison Snyder
// Pattern Program

#include <iostream>

using namespace std;

int main()
{
	int i;
	for(i = 2; i != 11; i++)
	{
		for(int p = 1; p != i; p++)
		{
			cout << "+";
		}
		cout << "\n";
	}
		for(i = 11; i != 2; i--)
	{
		for(int p = 1; p != (i-1); p++)
		{
			cout << "+";
		}
		cout << "\n";
	}
	return 0;
}

