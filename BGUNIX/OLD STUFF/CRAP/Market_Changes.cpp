// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "ctime"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int market_value;
	int market_change;
	int week;
	int random;
	int market_volatility;
	char a;

	week = 0; // intitial week
	market_value = 50; // initial market value
	cout << "Please enter market volatility: ";
	cin >> market_volatility; // max amount that the market can change per week
	cout << "Thank you." << endl;


	while (week < 50) // 50 = weeks before program closes
	{
		week++;
		cout << "Week #" << week << endl;
		market_change = (market_value - 50); // 50 here is the "average" market value, with the tendency to end up there.
		random = (rand()%100)+1;
		if(random < (48 + (.75 * market_change))) //40% chance for the market to drop
		{
			market_value -= (rand()%market_volatility);
		}
		if(random > (52 - (.75 * market_change))) //40% for the market to go up
		{
			market_value += (rand()%market_volatility);
		}
		cout << "The market value is now " << market_value << "." << endl;
		
	}
	cin >> a; // Move this statement up 2 lines to see results as they come in.
	return 0;
}

// Note to self: make the market have a higher volatity as the market_value deviates from the standard
// Also, try adding multiple "norms" to better replicate a real market curve

