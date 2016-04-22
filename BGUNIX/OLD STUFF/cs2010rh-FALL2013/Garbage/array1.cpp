#include <iostream>
#include <string>

using namespace std;

void findlow(string[], int, string&)

int main()
{
	//CONSTANTS
	const int MAX = 10;
	//VARIABLES
	string word[MAX];
	string low;
	int counter = 0;
	//////////////////////


	for(counter = 0; counter < MAX; counter++)
	{
		cin >> word[counter], MAX, low;
	}
	findlow(word);

	for(counter = 0; counter < MAX; counter++)
	{
		cout << word[counter] << "\n";
	}
}

void findlow(string[] tempword[], int MAX, string& low)
{
	low = tempword[0];
	for(int counter = 0; counter < MAX; counter++)
	{
		if(tempword[counter] > low)
			low = tempword[counter];
	}
	cout << "HIGHEST: " << low << "\n";
	return low;
}
