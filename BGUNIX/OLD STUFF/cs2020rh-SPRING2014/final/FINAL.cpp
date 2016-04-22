#include "iostream"
#include "string"
#include "Car.h"
#include "List.h"
#include "cstring"
#include "fstream"
#include "iomanip"

using namespace std;

void display(int);
void givevalues(char, List);
void centertext(string, int, char, bool, bool);

int main()
{
	string choice2;
	string make;
	string model;
	string color;
	string VIN;
	string tag;
	int year;
	int mileage;
	int value;
	bool NEW;
	List Lot;
	char choice = 0;
	int num;
	int w;

	cout << "Please designate width of console (in charcters spaces): ";
	cin >> w;
	while(w < 30)
	{
		cout  << "Width has a minimum of 30. Please reenter: ";
		cin >> w;
	}

	centertext("", w, '~', 1, 0);
	centertext(" Welcome to the Menu! ", w, '~', 1, 0);
	display(w);
	while(toupper(choice) != 'X')
	{
		centertext(" Please input choice:   ", w, '~', 1, 1);
		cin >> choice;
		choice = toupper(choice);
		switch(choice)
		{
		case 'X':
			centertext("Exiting program!\n\n", w, '~', 1, 0);
			exit(0);
		case 'A':
			centertext(" Creating new vehicle! ", w, '~', 1, 0);
			centertext(" For VIN and Dealer Tag, N/A is suggested. ", w, '~', 1, 0);
			centertext(" Please enter manufacturer:          ", w, '~', 1, 1);
			cin >> make;
			centertext(" Please enter model of car:          ", w, '~', 1, 1);
			cin >> model;
			centertext(" Please enter color of car:          ", w, '~', 1, 1);
			cin >> color;
			centertext(" Please enter VIN:                   ", w, '~', 1, 1);
			cin >> VIN;
			centertext(" Please enter dealer tag:            ", w, '~', 1, 1);
			cin >> tag;
			centertext(" Please enter year of car:        ", w, '~', 1, 1);
			cin >> year;
			centertext(" Please enter car mileage:        ", w, '~', 1, 1);
			cin >> mileage;
			centertext(" Please enter estimated value (MSRP if new):        ", w, '~', 1, 1);
			cin >> value;
			cout << "Is the car new? ";
			cin >> choice2;
			if(choice2 == "Yes" || choice2 == "YES" || choice2 == "Y" || choice2 == "y" || choice2 == "1")
				NEW = 1;
			else
				NEW = 0;
			Lot.add(make, model, color, VIN, tag, year, mileage, value, NEW);
			display(w);
			break;
		case 'I':
			centertext(" Inserting new vehicle! ", w, '~', 1, 0);
			cout << "When entering info for a vehicle, it is perfectly acceptable to input \"N/A\" for VIN or dealer tag.\n";
			cout << "Please enter manufacturer:           ";
			cin >> make;
			cout << "Please enter model of car:           ";
			cin >> model;
			cout << "Please enter color of car:           ";
			cin >> color;
			cout << "Please enter VIN:                    ";
			cin >> VIN;
			cout << "Please enter dealer tag:             ";
			cin >> tag;
			cout << "Please enter year of car:        ";
			cin >> year;
			cout << "Please enter car mileage:        ";
			cin >> mileage;
			cout << "Please enter estimated value (MSRP if new):       ";
			cin >> value;
			cout << "Is the car new? ";
			cin >> choice2;
			if(choice2 == "Yes" || choice2 == "YES" || choice2 == "Y" || choice2 == "y" || choice2 == "1")
				NEW = 1;
			else
				NEW = 0;
			cout << "Please enter number for where car is inserted (i.e. 2 will result in new car being after 2nd car): ";
			cin >> num;
			Lot.ins((num - 1), make, model, color, VIN, tag, year, mileage, value, NEW);
			display(w);
			break;
		case 'F':
			Lot.ins(0, "Dodge", "Dakota", "Silver", "819234DHS8235", "N/A", 2001, 99458, 1200, 0);
			Lot.load(Lot);
			Lot.del(1);
			display(w);
			break;
		case 'L':
			Lot.displaylist();
			display(w);
			break;
		case 'D':
			cout << "Please enter number for where car is deleted (i.e. 1 will result in 1st car being deleted): ";
			cin >> num;
			Lot.del(num - 1);
			display(w);
			break;
		}
	}

	Lot.add("Dodge", "Dakota", "Silver", "819234DHS8235", "N/A", 2001, 99458, 1200, 0);
	Lot.displaylist();
	Lot.load(Lot);
	Lot.displaylist();
	cin >> choice;
	return 0;
}

void display(int w)
{
	centertext("", w, '~', 1, 0);
	centertext("", w, '~', 1, 0);
	centertext("~  Add Vehicle     = A    ~", w, '~', 1, 0);
	centertext("~  Insert Vehicle  = I    ~", w, '~', 1, 0);
	centertext("~  Edit Vehicle    = E    ~", w, '~', 1, 0);
	centertext("~  Display Lot     = L    ~", w, '~', 1, 0);
	centertext("~  Delete Vehicle  = D    ~", w, '~', 1, 0);
	centertext("~  Load File       = F    ~", w, '~', 1, 0);
	centertext("~  eXit            = X    ~", w, '~', 1, 0);
	centertext("", w, '~', 1, 0);
	centertext("", w, '~', 1, 0);
	centertext("", w, '~', 1, 0);
	centertext("", w, '~', 1, 0);
}

void centertext(string string1, int spaces, char filler, bool right, bool back)
{
	if(string1.size() >= spaces)
	{
		cout << string1 << "\n";
		return;
	}
	char testit = ' ';
	char backspace = 8;
	int spacer = 0;
	int counter = 0;
	int length = string1.size();
	//Warning is a false positive, as no output is possible except 1 or 0...
	bool odd = (spaces - length) % 2; 
	if(odd)
		spaces++;
	else
		cout << filler;
	if((right && odd))
		cout << filler;
	while(counter != (((spaces - length) / 2)) - 1)
	{
		cout << filler;
		counter++;
	}
	cout << string1;
	counter = 0;
	while (counter != (((spaces - length) / 2)) - 1)
	{
		cout << filler;
		counter++;
	}
	if((odd == 1 && right == false) || odd == 0)
		cout << filler;
	if(back)
	{
		while(testit == ' ')
		{
			testit = string1[(string1.length() - spacer) - 1 ];
			spacer++;
		}
		for(counter; counter != -spacer + 1; counter--)
			cout << backspace;
	}
	else
		cout << "\n";
}