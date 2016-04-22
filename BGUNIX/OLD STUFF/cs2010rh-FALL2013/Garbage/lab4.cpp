////////////////////////////////////////////////////
//Project:                   Hotel Lab
//Programmer:                Addison Snyder
//Date:                      11/4/13
//Class:                     CS 2010 2:30 - 4:00 PM
//Description: This program allows hotel staff to
// enter info to find the overall hotel capacity
//ALL CODE IS MINE UNLESS OTHERWISE INDICATED
////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//VARIABLES
	int floors;
	int rooms;
	int occupied;
	int total_rooms = 0;
	int total_occupied = 0;
	int counter = 1;
	//WELCOME
	cout << "--------------------------------------------\n";
	cout << "--        Welcome to Dread\'s Hotel!       --\n";
	cout << "--------------------------------------------\n";
	//INPUT & LOOPS
	//Floors
	cout << "Please enter the number of floors,\nbecause we apparently don't know that...\n";
	cin >> floors;
	while(floors < 1)
	{
		cout << "Really? You get that many points for your pathetic answer.\nTry again!";
		cin >> floors;
	}
	//Rooms
	while(counter != floors)
	{
		if(counter == 13)
			counter++;
		cout << "How many rooms are on floor " << counter << " ? ";
		cin >> rooms;
		while(rooms < 10)
		{
			cout << "For whatever reason, there can't be less\nthan 10 rooms, but don't worry,\nthere can be a million!\nPlease reenter: ";
			cin >> rooms;
		}
		//Rooms Occupied
		cout << "Please enter the # of those rooms that are\ncurrently occupied: ";
		cin >> occupied;
		while (rooms < occupied)
		{
			cout << "You're slowly giving me an aneurysm.\nReenter: ";
			cin >> occupied;
		}
		//PROCESSING
		total_rooms += rooms;
		total_occupied += occupied;
		counter++;
	}
	//NEAT OUTPUT
	cout << "--------------------------------------------\n";
	cout << "--         TOTAL ROOMS:     " << setw(5) << total_rooms << "         --\n";
	cout << "--         TOTAL OCCUPIED:  " << setw(5) << total_occupied << "         --\n"; 
	cout << "--------------------------------------------\n";
	return 0;
}

