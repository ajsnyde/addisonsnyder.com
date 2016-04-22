#include <iostream>

using namespace std;
int main()
{
	char ans;
	while(ans != 'y')
	{
	cout << "Would you like to see the message? (y = yes)";
	cin >> ans;
	}
cout << "You answered yes!";
	return 0;
}
