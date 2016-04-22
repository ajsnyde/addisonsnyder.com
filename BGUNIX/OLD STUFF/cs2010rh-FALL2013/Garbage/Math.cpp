//Addison Snyder
//Math Tutor 5000
#include "iostream"
#include "ctime"
#include "cstdlib"

using namespace std;

int main()
{
	int num1;
	int num2;
	int answer;

	cout << "Hi! Welcome to Math Tutor! (Addison Snyder)\n";
	srand(time(NULL));
	num1 = rand() % 1000;
	num2 = rand() % 1000;
	cout << "\n "<< num1 << "\n";
	cout << "+" << num2 << "\n-----\n";
	cin >> answer;
	if(answer == (num1 + num2))
		cout << "Congrats!";
	else 
		cout << "You failed!";
	cin >> answer;

	return 0;
}

