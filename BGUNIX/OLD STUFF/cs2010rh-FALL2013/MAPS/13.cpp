// ConsoleApplication14.cpp : Defines the entry point for the console application.
//
////////////////////////////////////////////////////////
//Addison Snyder
//DREAD'S MAP UTILITY
//Start Date: 12/15/13
//Version:
#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "ctime"
#include "cstdlib"
#include "iomanip"
using namespace std;
//STRUCT DECLARATIONS
struct tile_type
{
	string type_name;
	char letter;
	int color;
	int ID;
	double base_chance;
	double chance_factor;
};
struct tile // For specific tiles on the map. Ex. "Woods - Elven - Hostile"
{
	string tile_name;
	string type_name;
};
//FUNCTION PROTOTYPES

char menu();								// Shows menu and gets input
void edit_tile_types(tile_type[], int&);	// Allows easy changes to be made to the tiles previously created in create_tiles()
void mapgen(tile_type[], int&);				// Makes map using input from create_tiles() and edit_tiles(). Also gets map length and height
void create_tiles(tile_type[], int&);		// Creates initial tilesfrom user input
//CONSTANTS
void load_tiles(tile_type[], int&);			//Loads tile types from a file
const int MAX_TILES = 20;					// Max number of tile types
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
	//VARIABLES:
	tile_type TileType[MAX_TILES];//Array of struct "tile_type"; (ex. TileType[1].type_name will provide the name of 1st tile)
	char choice = '='; // Set choice to be something for the switch to compare to.
	srand(time(NULL)); // Seeds random numbers
	int num_custom_tiles = 0; // keeps track of the amount of tile types
	cout << "Welcome to Dread's Map Utility!\n"; // WELCOME
	while(choice != 'X') // General loop for the entire program
	{
		choice = menu();// shows menu and returns input
		switch(choice) // The "switchboard" for the program
		{
			case 'C':
				create_tiles(TileType, num_custom_tiles);
				break;
			case 'E':
				edit_tile_types(TileType, num_custom_tiles);
				break;
			case 'M':
				mapgen(TileType, num_custom_tiles);
				break;
			case 'L':
				load_tiles(TileType, num_custom_tiles);
				cout << "Area under construction.\n";
				break;
			case 'S':
				cout << "Area under construction.\n";
				break;
			case 'X': //Immediately kills the program
				exit(0);
			default:
				cout << "\"" << choice << "\" is not a valid choice!\n";
				break;
	
		}
	}
	////////////////////////////////////// Testing garbage...

	cin >> choice;
	//////////////////////////////////////


	return 0;
}


char menu() // MENU
{
	char choice;

	cout << "\n";
	cout << "Main Menu\n";
	cout << "L = Loading\n";
	cout << "S = Saving\n";
	cout << "C = Create Tiles\n";
	cout << "E = Edit Tile Properties\n";
	cout << "M = Make Map\n";
	cout << "X = Exit\n";
	cout << "Please choose an option: ";
	cin >> choice;

	return choice;
}

void create_tiles(tile_type tile[], int& temp_num_custom_tiles) // TILE CREATION!
{
	int i = 0; // set counter
	cout << "Welcome to tile creation. Here, you will be able to make your own custom terrains.\n"; // WELCOME

	while(i != MAX_TILES) // Prevents more than (20?) tile types from being created
	{
		cout << "Please enter name of the terrain type (i.e. Woods). To stop, enter STOP: ";
		cin >> tile[i].type_name; // general name of tile
		if(tile[i].type_name == "STOP")
		{
			tile[i].type_name = ""; //Prevents future errors, cleans up array
			temp_num_custom_tiles = i; // set num of tile types, very important throughout program
			break; // Go back to the menu!
		}

		cout << "Now enter a character that will represent this terrain on a map: ";
		cin >> tile[i].letter; // char that shows up on map
		cout << "Please enter this terrain's color code: ";
		cin >> tile[i].color;
		cout << "Please enter base chance: ";
		cin >> tile[i].base_chance; // base # of "tickets"
		cout << "Please enter chance factor: ";
		cin >> tile[i].chance_factor; // num to multiply base # by when a tile of the same type is adjacent; creates clumping
		tile[i].ID = i; // sets up tile_ID, allows for an easy recall of a tile type
		i++; //counter
	}
}

void edit_tile_types(tile_type tile[], int& temp_num_custom_tiles)
{
	int tile_selection;
	char tile_attribute;
	if(temp_num_custom_tiles == 0)
	{
		cout << "No tiles have been detected. Please create some first.\n\n"; // Prevents lack of tiles to edit
		return;
	}
	int i = 0;
	cout << "Custom Tiles So Far:\n";
	for(int i = 0; i != temp_num_custom_tiles; i++)
	{
		cout << setw(2) << i << " --- NAME - " << tile[i].type_name << " --- CHARACTER/COLOR - {" << tile[i].letter << "}\n";
		cout << "   --- BASE - " << setw(4) << tile[i].base_chance << " --- CHANCE FACTOR - " << tile[i].chance_factor << "\n";
	}
	cout << "Num tiles = " << temp_num_custom_tiles << "\n";
	do // used to check input
	{
		cout << "Select a valid tile # to edit: ";
		cin >> tile_selection;
		
	} while(tile_selection < 0 || tile_selection >= temp_num_custom_tiles);
	

	while(tile_selection != 'X') //Used to edit tiles!
	{
		cout << setw(2) << tile_selection << " --- NAME - " << tile[tile_selection].type_name << " --- CHARACTER/COLOR - {" << tile[tile_selection].letter << "}\n"; //displays the tile the user entered
		cout << "   --- BASE - " << setw(4) << tile[tile_selection].base_chance << " --- CHANCE FACTOR - " << tile[tile_selection].chance_factor << "\n";
		cout << "N = NAME\n";
		cout << "L = Letter\n";
		cout << "C = Color\n";
		cout << "B = Base Chance\n";
		cout << "F = Chance Factor\n";
		cout << "Choose an attribute to modify (X to exit): ";
		cin >> tile_attribute;
		switch (tile_attribute)
		{
		case 'N':
			cout << "Please enter a new name: ";
			cin >> tile[tile_selection].type_name;
			break;
		case 'L':
			cout << "Please enter a new letter: ";
			cin >> tile[tile_selection].letter;
			break;
		case 'C':
			cout << "Please enter a new color code: ";
			cin >> tile[tile_selection].color;
			break;
		case 'B':
			cout << "Please enter a new Base Chance: ";
			cin >> tile[tile_selection].base_chance;
			break;
		case 'F':
			cout << "Please enter a new Chance Factor: ";
			cin >> tile[tile_selection].chance_factor;
			break;
		case 'X':
			return;
		default:
			cout << "Please enter a valid selection.\n";
		}
	}
}

void mapgen(tile_type tile[], int& temp_num_custom_tiles)
{
	int max_x = 0;	// Map dimensions
	int max_y = 0;
	int mapy = 0;	//counters for x and y
	int mapx = 0;
	double old_chance_x;	// Used to prevent crashes
	double old_chance_y;
	double chance_accum[MAX_TILES];	//used in chance process
	int accum = 0;
	long double chance;		// Used for random numbers
	int accum_int;
	tile_type map[70][200]; // This is the actual map.

	if(temp_num_custom_tiles < 1)//prevents user from crashing program by having no tiles
	{
		cout << "You don't have any tiles to create a map with!\n";
		return; // return to menu
	}
	cout << "Please enter map length (1-70): "; //Actual maxes depend on the system and hardware.
	cin >> max_x;
	cout << "Please enter map height (1-1000): ";
	cin >> max_y;

	////////////////////////////
	int tile_selection;
	for(tile_selection = 0; tile_selection < temp_num_custom_tiles; tile_selection++) // Used for debugging. Will keep for awhile.
	{
		cout << setw(2) << tile_selection << " --- NAME - " << tile[tile_selection].type_name << " --- CHARACTER/COLOR - {" << tile[tile_selection].letter << "}  ID: " << tile[tile_selection].ID << "\n";
		cout << "   --- BASE - " << setw(4) << tile[tile_selection].base_chance << " --- CHANCE FACTOR - " << tile[tile_selection].chance_factor << "\n";
	}
	////////////////////////////
	
	while(mapy != (max_y)) // This is for having different rows
	{
		while(mapx != (max_x)) // Moving one tile at a time..
		{
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// EXTRA CHANCE - This part makes the tiles tend to "clump" by modifying chances of getting a specific tile type based on the precence of similar tiles that are adjacent
			if(mapx != 0)//Makes sure this only happens when their is a tile to the left to get attributes from
			{
				if(map[(mapx - 1)][mapy].chance_factor <= 0) // Prevents errors (dividing by zero) and destroying chance proccess through negatives (they will now act like zeros)
				{
					old_chance_x = tile[map[(mapx - 1)][mapy].ID].base_chance; // basically takes the base chance of the tile to the left for temp storage
					tile[map[(mapx - 1)][mapy].ID].base_chance = 0;			   // makes the base chance zero temporarily
				}
				else // Happens when no input protection is needed (i.e. BASE = 10, CHACE FACTOR = 1.5)
					tile[map[(mapx - 1)][mapy].ID].base_chance *= map[(mapx - 1)][mapy].chance_factor; // multiplies the base and factor (temporarily)
			}
			if(mapy != 0)// This part is a modification of the above code, except applies to the tile ABOVE
			{
				if(map[mapx][(mapy - 1)].chance_factor <= 0) 
				{
					old_chance_y = tile[map[mapx][(mapy - 1)].ID].base_chance;
					tile[map[mapx][(mapy - 1)].ID].base_chance = 0;
				}
				else
					tile[map[mapx][(mapy - 1)].ID].base_chance *= map[mapx][(mapy - 1)].chance_factor;
			}
			////////////////////////////////////////////END OF CHANCE MODIFICATION//////////////////////////////////////////////////////////////////////////////////////////////
			//SETS UP CHANCE ARRAY FOR EASY CALCULATION OF TILE (through a 1 dim. array called chance_accum)
			for(int i = 0; i < temp_num_custom_tiles; i++)	//Sets up an array so the "tickets" can be drawn randomly (and easily, systematically, etc.).
			{
				accum += tile[i].base_chance; //keeps adding chances to create a staggered set of numbers used to calculate odds.
				chance_accum[i] = accum;	  //puts those numbers in an array for easy accesibility
			}
			chance = rand() % accum; //This is where a value is chosen, ranging from 1-(all base_chances  with their modifications)
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// ASSIGNS "MAP" ARRAY FULL OF TILE STRUCTs USING PREVIOUS ARRAY (1-dimens.)
			for(int i = 0; i < temp_num_custom_tiles; i++)//This loop decides what tile type goes where
			{
				if(chance <= chance_accum[i])// decides what tile is selected using the corresponding random number
				{
					map[mapx][mapy] = tile[i];// "i" essentially represents tile ID
					break; //Yay, we found the tile type and it has been placed correctly! Time to move on to the next one!
				}
			}
			// Before moving on to the next tile, we need to "unmodify" the base chances.
			if(mapx != 0)// This only occurs if they were changed originally
			{
				if(map[(mapx - 1)][mapy].chance_factor <= 0) //returns the old value if it would be irreplacably modified through zero.
					tile[map[(mapx - 1)][mapy].ID].base_chance = old_chance_x;
				else
					tile[map[(mapx - 1)][mapy].ID].base_chance /= map[(mapx - 1)][mapy].chance_factor; //otherwise, it just reverses the process (I am unsure of how perfectly accurate this is. Might (probably won't) change over MANY repetitions)
			}
			if(mapy != 0)//Same for tile ABOVE
			{
				if(map[(mapx)][mapy - 1].chance_factor <= 0)
					tile[map[(mapx)][(mapy - 1)].ID].base_chance = old_chance_y;
				else
					tile[map[(mapx)][mapy - 1].ID].base_chance /= map[mapx][(mapy - 1)].chance_factor;
			}
			// Displays the tile!
			std::cout << "\033" << "[" << 0 << ";" << map[mapx][mapy].color << "m" << map[mapx][mapy].letter  <<  "\033" << "[m" << std::endl;
			accum = 0;// Resets accum
			mapx++;
		}
		mapx = 0;
		cout << "\n";// adds newline for the next row
		mapy++;
		//END of actual assignment to the MAP array of structs.
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	mapy = 0; //resets y counter for multiple creations using the same terrain stats.
	return;
}

void load_tiles(tile_type tile[], int& temp_num_custom_tiles)
{
	string file_name;
	string file;
	cout << "Welcome to Loading! Please enter a file name to load tile types from: ";
	cin >> file_name;
	ofstream outputFile;
	ifstream inputFile;
	int i = 0;	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////	inputFile.open(file_name);     ////////////////////////////////////////////////////
	//// Unfortunately, Linux doesn't want to compile this line. I've followed procedures in the textbook, and resorted to resources online.
	//// I've tried using string literals with atatched code (c_str) as well, with no luck.
	//// Because I've worked hard on it and it works on Windows, I was hoping you could give me full credit for the attempt to put it on Linux
	//// If in doubt of its capabilities, feel free to download the .exe of my program along with "new.txt". This section of the program works.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inputFile >> file; // Gets number of tiles; at beginning of txt file
	temp_num_custom_tiles = atof(file.c_str()); //converts string to int. Credit to Cplusplus.org.

	while(i != temp_num_custom_tiles)
	{
		inputFile >> file; // reads first string from txt (automatically seperated by spaces)
		tile[i].type_name = file;
		cout << file << " has been written as tile name!\n";
		inputFile >> file;
		tile[i].letter = file[0];
		cout << file << " has been written as tile character!\n";
		inputFile >> file;
		tile[i].color = atof(file.c_str());
		cout << file << " has been written as color code!\n";
		inputFile >> file;
		tile[i].base_chance = atof(file.c_str());
		cout << file << " has been written as base chance!\n";
		inputFile >> file;
		tile[i].chance_factor = atof(file.c_str());
		cout << file << " has been written as chance factor!\n";
		inputFile >> file;
		tile[i].ID = atof(file.c_str());
		cout << file << " has been written as ID #!\n";
		cout << "------------------------------------------------------\n";//seperates tile types for added readability
		i++;
	}
	cout << "\nDONE!\n";//Confirms that proccess ran smoothly
	return;
}


/* ORIGINAL STRUCT snippet - Produced run-time errors... (overly complicated...)

	while(mapy != (max_y))
	{
		while(mapx != (max_x))
		{
			
			

			if(mapx != 0)
			{
				area_left = map[(mapx - 1)][mapy];
				oringinal_chance_left = tile[area_left.ID].base_chance;
				tile[area_left.ID].base_chance = (tile[area_left.ID].base_chance * tile[area_left.ID].chance_factor); 
			}
			if(mapy != 0)
			{
				area_up = map[mapx][(mapy - 1)];
				original_chance_up = tile[area_up.ID].base_chance;
				tile[area_up.ID].base_chance = (tile[area_up.ID].base_chance * tile[area_up.ID].chance_factor);
			}

			for(int i = 0; i < temp_num_custom_tiles; i++)	//Sets up an array so the "tickets" can be drawn randomly (and easily, systematically, etc.).
			{
				accum += tile[i].base_chance;
				chance_accum[i] = accum;
			}

			if(mapy != 0)
				tile[area_up.ID].base_chance = original_chance_up;
			if(mapx != 0)
				tile[area_left.ID].base_chance = oringinal_chance_left;

			


		//	accum_int = (1000 * accum); //since the rand() function doesn't accept doubles, I will try to increase accuracy...
		//	cout << accum_int;
			chance = rand() % accum;
		//	chance /= 1000;

			for(int i = 0; i < temp_num_custom_tiles; i++)
			{
				if(chance <= chance_accum[i])
				{
					map[mapx][mapy] = tile[i];
					break;
				}
			}
			cout << map[mapx][mapy].letter;
			accum = 0;
			mapx++;
		}
		mapx = 0;
		cout << "\n";
		mapy++;
	}
	mapy = 0;
	*/