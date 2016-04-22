//Addison Snyder
// n! calculator

#include <iostream>

using namespace std;

int main()
{
	int num = 1;
	long int accum = 0;

	while(num != 0)
	{
		cout << "Hello! Welcome to the n! calculator!\nPlease Enter a number: ";
		cin >> num;
		
		if(num > 0)
		{
			while (num != 0)
			{			
				accum += num;
				num--;
			}
		cout << "Here's your number: " << accum << "\n"; 
		}
	}
	return 0;
}
