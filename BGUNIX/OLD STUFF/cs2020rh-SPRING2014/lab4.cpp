//All code by Addison Snyder
//2/24/2014
//lab4.cpp - struct program
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct tile//struct definition
{
int id;
string type;
int color;
double chance;
double factor;
bool land;
};
//prototypes
void fill_array(tile[]);
void display(tile[]);
void search(tile[]);

const int MAX = 10; // size of struct array - NOT dependent on number of structs in file.
ifstream input;//creates input stream

int main()
{
	tile tile_type[MAX];
	fill_array(tile_type);
	display(tile_type);
	search(tile_type);
	return 0;
}

void fill_array(tile temptile[])//(attempts) to take data from "file.txt" and integrate it into the array of structs previously created in main()
{
	int i = 0;//used for designating which struct is getting data
	input.open("file.txt");//open file
	if(input.fail())//kills program if file not found or is otherwise inaccesible
	{
		cout << "Cannot open file! Terminating Program!\n";
		exit(1);//exits entire program with error code 1
	}
	else
		cout << "File loaded!\n";//success!

	input >> temptile[i].id;//seeding loop

	while(!input.eof())//stops at end of file. MAX still determines the actual max of entries, and could potentially write beyond the array's limit.
	{
		input >> temptile[i].type;
		input >> temptile[i].color;
		input >> temptile[i].chance;
		input >> temptile[i].factor;
		input >> temptile[i].land;
		i++;
		input >> temptile[i].id;
	}

// This loop also could have also worked, without the need to seed or worry about reading past the file
//	for(int i = 0; !input.eof(); i++)
//	{
//		input >> temptile[i].id;
//		input >> temptile[i].type;
//		input >> temptile[i].color;
//		input >> temptile[i].chance;
//		input >> temptile[i].factor;
//		input >> temptile[i].land;
//	}
	cout << "File loading complete!\n\n";
	return;
}

void display(tile temptile[])//displays all struct elements in a useful manner
{
	cout << "Displaying structs:\n";

	for(int i = 0; i < MAX; i++)//nothing special here
	{
		cout << "ID: " << temptile[i].id << "\n";
		cout << "Type: " << temptile[i].type << "\n";
		cout << "Color Code: " << temptile[i].color << "\n";
		cout << "Chance: " << temptile[i].chance << "\n";
		cout << "Chance Factor: " << temptile[i].factor << "\n";
		cout << "Land: " << temptile[i].land << "\n\n";
	}
	return;
}

void search(tile temptile[])
{
	int ID;
	cout << "Please enter an ID to search for: ";
	cin >> ID;
	cout << "ID: " << temptile[ID].id << "\n";
	cout << "Type: " << temptile[ID].type << "\n";
	cout << "Color Code: " << temptile[ID].color << "\n";
	cout << "Chance: " << temptile[ID].chance << "\n";
	cout << "Chance Factor: " << temptile[ID].factor << "\n";
	cout << "Land: " << temptile[ID].factor << "\n\n";
}