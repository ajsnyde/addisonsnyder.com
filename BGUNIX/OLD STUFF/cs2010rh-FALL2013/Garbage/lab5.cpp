////////////////////////////////////////////////////
//Project:                   Rent Lab
//Programmer:                Addison Snyder
//Date:                      11/21/13
//Class:                     CS 2010 2:30 - 4:00 PM
//Description: This program allows customers to
// calculate their rental payments.
//ALL CODE IS MINE UNLESS OTHERWISE INDICATED
////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;

//LATE FEE % - global constant for easy and universal modification...
const double LATE_FEE        = 0.1;
//Days before a late fee is applied - for easy and universal modification...
const int    DAYS_BEFORE_FEE = 10;

//PROTOTYPES!
void displayWelcome();
void getData(double&, int&);
double calculateLateFee(double rent_amount, int late);
double calculateTotalDue(double rent_amount, double late_fee);
void displayResults(double rent, double late_fee, double total_due, int days_late);


//MAIN
int main()
{
	//Variables in order of appearence
	double rent;
	int days_late;
	double late_fee;
	double total;

	//FUNCTION CALLS
	displayWelcome();
	getData(rent, days_late);
	late_fee = calculateLateFee(rent, days_late);
	total = calculateTotalDue(rent, late_fee);
	displayResults(rent, late_fee, total, days_late);

	//END
	return 0;
}

//OUTPUT - WELCOME MESSAGE
void displayWelcome()
{
	cout << "#############################################\n";
	cout << "####             Welcome to              ####\n";
	cout << "####        Dread's Renting Tool         ####\n";
	cout << "#############################################\n";
}


//INPUT
void getData(double& temprent, int& tempdayslate)
{
	cout << "Please enter your rent: ";
	cin >> temprent;
	while(temprent < 0)
	{
		cout << "Sorry, no negative numbers! Try again: ";
		cin >> temprent;
	}
	cout << "Please enter days late: ";
	cin >> tempdayslate;
	while(tempdayslate < 0)
	{
		cout << "No negatives. Please try again: ";
		cin >> tempdayslate;
	}
	return;
}

//PROCESSING
double calculateLateFee(double rent, int late)
{
	double template_fee = 0;
	if(late >= DAYS_BEFORE_FEE)
	{
		template_fee = (rent * LATE_FEE);
	}
	return template_fee;
}

//MORE PROCESSING
double calculateTotalDue(double temprent, double template_fee)
{
	double temptotal = (temprent + template_fee);
	//That seemed efficient...
	return temptotal;
}

//PROCESSED OUTPUT
void displayResults(double rent, double late_fee, double total, int days_late)
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~ Monthly Rent: $" << fixed << setprecision(2) << right << setw(7) << rent << " Days Late: " << right << setw(3) << days_late << " ~~~\n";
	cout << "~~~ Late Fee:     $" << fixed << setprecision(2) << right << setw(7) << late_fee << "                ~~~\n";
	cout << "~~~ Total Due:    $" << fixed << setprecision(2) << right << setw(7) << total <<    "                ~~~\n";
	cout << "~~~ Thanks for using Dread's Rental Tool! ~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
