//Addison Snyder
#include "iostream"
#include "iomanip"

using namespace std;

int adult_tickets = -1, kid_tickets = -1, senior_tickets = -1;

int main()
{
	cout << "Hello! Welcome to the TicketMaster 9000.\n";
	cout << "Adult tickets are    $9.50\nKid's tickets are    $3.00\nSenior tickets are   $5.00\n";
	
	while(adult_tickets < 0)
	{
	cout << "\nHow many adult tickets do you want? ";
	cin >> adult_tickets;
	}

	while(kid_tickets < 0)
	{
	cout << "\nHow many kid's tickets do you want? ";
	cin >> kid_tickets;
	}
	
	while(senior_tickets < 0)
	{
	cout << "\nHow many senior tickets do you want? ";
	cin >> senior_tickets;
	}
	cout << "\n\n\a\a\a";
	cout << "\nThat will come out to be: $" << setprecision(2) << fixed << ((adult_tickets * 9.5) + (kid_tickets * 3) + (senior_tickets * 5));
	cout << "\n\nPlease enter credit card number, PIN, social security #, driver's licence stats, and all personal documents and passwords: ";
	cin >> senior_tickets;
	cout << "\n\nThanks for shopping at the one and only TicketMaster 9000!\n";

	return 0;
}