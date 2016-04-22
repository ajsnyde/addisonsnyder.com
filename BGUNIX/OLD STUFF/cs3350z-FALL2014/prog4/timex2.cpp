// File timex.cpp version of November 2014.
// Based on code and comments written by Walter Maner unless credited otheriwse.
#include <iostream>
#include <iomanip>
#include <math.h>
#include "Timer.h"
#include "vector"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

double doNothing( double &arg )
{
	return arg;
}

void mystSort1( vector<string> & );
void mystSort2( vector<string> & );
string create_string();
vector<string> create_vector(int);
void display_vector(vector<string> &, int);

int main()
{
	Timer aTimer1, aTimer2, aTimer3, aTimer4;
	double junk;
	int n = 10000;
	const long int REPS = 10;  // Determined by trial and error
	Timer timer1[REPS], timer2[REPS], timer3[REPS], timer4[REPS], control1[REPS], control2[REPS], control3[REPS], control4[REPS];
	srand (time(NULL));
	vector<string> master = create_vector(n);

	for(n = 5000; n <= 40000; n*=2)
	{
		cout << "Starting Experiment 3 (list sort). . .\n";
		cout << "REP #\tN\tTIME\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		for(int i = 0; i < REPS; i++)
		{
			timer3[i].start();
			std::sort (master.begin(), master.end());
 			master = create_vector(n);
			timer3[i].stop();
			cout << i << "\t" << n << "\t" << fixed << setprecision( 11 ) << timer3[i].getElapsedTime() << "\n";
		}

	cout << "\n\nINCREASING N TO " << (n*2) << ". . .\n\n";
	}
	return 0;
}

string create_string()
{
	string str = "default!";
	for(int i = 0; i<8; i++)
	{
		str[i] = rand() % 26 + 65;
	}
	str[8] = 0;
	//cout << str << endl;
	return str;
}

vector<string> create_vector(int ELEMENTS)
{
	vector<string> vect;
	for(int i = 0; i<ELEMENTS; i++)
		vect.push_back(create_string());
	return vect;
}

void display_vector(vector<string> & vect, int ELEMENTS)
{
	for(int i = 0; i<ELEMENTS; i++)
		cout << vect[i] << endl;
	return;
}
