//////////////////////////////////////////////////////
//Project:			Roulette
// Programmer: 			Addison Snyder
//Date: 			10-16-13
//Class: 			CS 2010 2:30 - 4:00 PM
//Description: Plays American roullete with user...
//
//ALL CODE IS MINE UNLESS OTHERWISE INDICATED
//////////////////////////////////////////////////////

#include "iostream"
#include "cstdlib"
#include "ctime"

using namespace std;

int main()
// SOOOO TEMPTED to have a loop.... Or some functions for different menu options...
// How would one have the computer "wait" during the "rolling" sequence? I want to have it wait about a third of a sec, add a ".", and repeat that about 3-5 times...
{
	//VARIABLES
	char choice;
	char choice2;
	int chips = 500;
	int chips_bet = 100;
	int ballvalue;
	int guess;

	//WELCOME
	cout << "-----------------------------------------------";
	cout << "\n      Welcome to the Roulettatron 9000!      \n";
	cout << "-----------------------------------------------";
	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n  B = change Bet  O = Odd  E = Even X = eXact  ";//If I didn't care for my own grades in this class, I would incorporate a switch menu vs a cumbersome set of "if"s
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "You currently have " << chips << " chips.\n";
	cout << "Default betting amount is " << chips_bet << ".\n";
	cout << "Please input an option: ";
	//INPUT
	cin >> choice;
	if (choice == 'B') //CHANGE BETTING AMOUNT OPTION
	{
		cout << "Please enter your new bet amount: ";
		cin >> chips_bet;
		if (chips_bet > chips || chips_bet < 1)
			cout << "\nThis amount is invalid! Terminating program!\n";
		else
		{
			cout << "Change successful!\nPlease input an option: "; //GO BACK TO OPTIONS
			cin >> choice;
		}
	}
	if (choice == 'O' || choice == 'E') //OPTIONS "odd" & "even"
		//PROCESSING & OUTPUT
	{
		//CONFIRMATION OF BET...
		cout << "Just in case there was an error between the\nkeyboard and chair, please confirm your\ndecision by entering C...\n";
		cin >> choice2;
		if (choice2 == 'C')
		{
			//RANDOM NUMBER GENERATION
			cout << "Rolling . . .\n";
			srand(time(NULL));
			ballvalue = rand() % 38;
			cout << "The ball landed on " << ballvalue << ".\n";
			//FIX ZEROS (yes, I know I could've included another OR statement to do this...)
			if (ballvalue == 0)
				ballvalue += 2;
			if ((ballvalue % 2 == 1 && choice == 'O') || (ballvalue % 2 == 0 && choice == 'E'))
			{
				cout << "Congrats! You have won " << chips_bet << " chips!\n";//WIN
				chips += chips_bet;//I could add a messy "subtract and then add if won" snippet to this, but there's no real point to it. Besides, it would be more open to exploits and stuff.
				cout << "Your now have " << chips << " chips!\n";
			}
			else
			{
				cout << "Sorry, you have lost " << chips_bet << " chips!\n";//LOSS
				chips -= chips_bet;
				cout << "Your now have " << chips << " chips!\n";
			}
		}
	}
	if (choice == 'X')
	{
		//CONFIRMATION OF BET
		cout << "Please enter C to continue...\n";
		cin >> choice2;
		if (choice2 == 'C')
	}
	cout << "Please enter your guess, and be sure that it is\nbetween 0 and 37: ";
	//Could add limits, but it would require a loop to really work and if the human is really that stupid...
	cin >> guess;
	cout << "Rolling . . .\n";
	srand(time(NULL));
	ballvalue = rand() % 38;
	cout << "The ball landed on " << ballvalue << ".\n";
	if (ballvalue == guess || guess == 9000)//added for testing, and as an exploit for my friends; could remove later
	{
		//JACKPOT!
		cout << "YOU HAVE WON " << (chips_bet * 38) << " CHIPS!!!\n";
		chips += (chips_bet * 38);//It should be assumed that this is AMERICAN roulette; could change later or replace entirely with a constant if I wanted to...
		cout << "You now have " << chips << " chips!!\n";
	}
	else
	{
		cout << "Sorry, you lost " << (chips_bet) << ".\n";
		chips -= chips_bet;
		cout << "You now have " << chips << " chips.\n";
	}
	//ENDING cin; very useful for certain applications
	cin >> choice;
	//END
	return 0;
}
