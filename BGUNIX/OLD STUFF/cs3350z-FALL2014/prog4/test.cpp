// Time.cpp : Defines the entry point for the console application.
//
#include "iostream"
#include "vector"
#include <stdlib.h>
#include <time.h>

#include "string"

using namespace std;

void mystSort1( vector<string> & );
void mystSort2( vector<string> & );
string create_string();
vector<string> create_vector(int);
void display_vector(vector<string> &, int);

int main()
{
	int test;
	srand (time(NULL));
	vector<string> master = create_vector(400);
	vector<string> vect = master;
	


	cin >> test;
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
