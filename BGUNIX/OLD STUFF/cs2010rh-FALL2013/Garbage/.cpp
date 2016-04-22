#include <iostream>
#include <string>

using namespace std;

string findlow(string[]);

int main()
{
	//CONSTANTS
	const int MAX = 10;
	//VARIABLES
	string word[MAX];
	string low;
	int counter = 0;
	/////


	for(counter = 0; counter < MAX; counter++)
	{
		cin >> word[counter];
	}
	low = findlow(word);
	cout << "HIGHEST: " << low << "\n";
	for(counter = 0; counter < MAX; counter++)
	{
		cout << word[counter] << "\n";
	}
}

string findlow(tempword[])
{
	low = tempword[0];
	for(counter = 0; counter < MAX; counter++)
	{
		if(tempword[counter] > low)
			low = tempword[counter];
	}
	return low;
}
