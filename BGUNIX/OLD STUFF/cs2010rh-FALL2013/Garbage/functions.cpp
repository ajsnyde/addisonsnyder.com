#include <iostream>

using namespace std;

double getscore();
char calculateletter(double);
void displaylettergrade(char);

int main()
{
	char lettergrade;
	double gradescore;

	cout << "Hello. Please enter your grade percent: ";
	gradescore = getscore();
	lettergrade = calculateletter(gradescore);
	displaylettergrade(lettergrade);
	return 0;
}

double getscore()
{
	double score;
	cin >> score;
	return score;
}

char calculateletter(double score)
{
	char letter;
	if(score >= 90)
		letter = 'A';
	else if(score >= 80)
		letter = 'B';
	else if(score >= 70)
		letter = 'C';
	else if(score >= 60)
		letter = 'D';
	else
		letter = 'F';

	return letter;
}

void displaylettergrade(char letter)
{
	cout << "Letter grade = " << letter;
	cout << "\nHave a nice day!";
	return;
}
