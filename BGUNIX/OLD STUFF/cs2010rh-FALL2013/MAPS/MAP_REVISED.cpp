////////////////////////////////////////////////////////
//Addison Snyder
//DREAD'S MAP UTILITY
//Start Date: 12/15/13
//Version:
////////////////////////////////////////////////////////
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
char menu();
void edit_tile_types(tile_type[], int&);
void mapgen(tile_type[], int&);
void create_tiles(tile_type[], int&);
//CONSTANTS
const int MAX_TILES = 20;
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
	//VARIABLES:
	tile_type TileType[MAX_TILES];//Array of struct "tile_type"; (ex. TileType[1].type_name will provide the name of 1st tile)
	char choice = 'A';
	int num_custom_tiles = 0;
	cout << "Welcome to Dread's Map Utility!\n";
	while(choice != 'X')
	{
		choice = menu();
		switch(choice)
		{
			case 'C':
				create_tiles(TileType, num_custom_tiles);
				break;
			case 'E':
				edit_tile_types(TileType, num_custom_tiles);
				break;
			case 'M':
				mapgen(TileType, num_custom_tiles);
				cout << "Area under construction.\n";
				break;
			case 'L':
				cout << "Area under construction.\n";
				break;
			case 'X':
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


char menu()
{
	char choice;


	cout << "\n";
	cout << "Main Menu\n";
	cout << "L = Loading\n";
	cout << "C = Create Tiles\n";
	cout << "E = Edit Tile Properties\n";
	cout << "M = Make Map\n";
	cout << "X = Exit\n";
	cout << "Please choose an option: ";
	cin >> choice;
	return choice;
}

void create_tiles(tile_type tile[], int& temp_num_custom_tiles)
{
	int i = 0;
	cout << "Welcome to tile creation. Here, you will be able to make your own custom terrains.\n";

	while(i != MAX_TILES)
	{
		cout << "Please enter name of the terrain type (i.e. Woods). To stop, enter STOP: ";
		cin >> tile[i].type_name;
		if(tile[i].type_name == "STOP")
		{
			tile[i].type_name = "";
			temp_num_custom_tiles = i;
			break;
		}

		cout << "Now enter a character that will represent this terrain on a map: ";
		cin >> tile[i].letter;
		cout << "Please enter this terrain's color code: ";
		cin >> tile[i].color;
		cout << "Please enter base chance: ";
		cin >> tile[i].base_chance;
		cout << "Please enter chance factor: ";
		cin >> tile[i].chance_factor;
		tile[i].ID = i;
		i++;
	}
}

void edit_tile_types(tile_type tile[], int& temp_num_custom_tiles)
{
	int tile_selection;
	char tile_attribute;
	if(temp_num_custom_tiles == 0)
	{
		cout << "No tiles have been detected. Please create some first.\n\n";
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
	do
	{
		cout << "Select a valid tile # to edit: ";
		cin >> tile_selection;
		
	} while(tile_selection < 0 || tile_selection >= temp_num_custom_tiles);
	

	while(tile_selection != 'X')
	{
		cout << setw(2) << tile_selection << " --- NAME - " << tile[tile_selection].type_name << " --- CHARACTER/COLOR - {" << tile[tile_selection].letter << "}\n";
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
	int max_x = 0;
	int max_y = 0;
	int mapy = 0;
	int mapx = 0;
	double chance_accum[MAX_TILES];
	long double accum = 0;
	long double chance;
	int accum_int;
	tile_type area_left;
	tile_type area_up;
	tile_type default_type = {"Default", 'D', 30, 20, 1, 1};
	tile_type map[10][10];


	cout << "Please enter map length (1-200): ";
	cin >> max_x;
	cout << "Please enter map height (1-1000): ";
	cin >> max_y;

	while(mapy != (max_y))
	{
		while(mapx != (max_x))
		{
	//		if(mapx != 0)
	//			area_left = map[(mapx - 1)][mapy];
	//		else
	//			area_left = default_type;
	//		if(mapy != 0)
	//			area_up = map[mapx - 1][(mapy)];
	//		else
	//			area_up = default_type;
	//		cout << "ID: " << area_left.ID;
	//		cout << "\ndone";
	//		tile[area_left.ID].base_chance *= tile[area_left.ID].chance_factor;  // Calculates chance with adjacent tiles.
	//		tile[area_up.ID].base_chance *= tile[area_up.ID].chance_factor;		 //ex. 88 (BASE) * 1.16 = new BASE.
			
			for(int i = 0; i < temp_num_custom_tiles; i++)	//Sets up an array so the "tickets" can be drawn randomly (and easily, systematically, etc.).
			{
				accum += tile[i].base_chance;
				chance_accum[i] = accum;
			}

		//	tile[area_left.ID].base_chance /= tile[area_left.ID].chance_factor;  // REVERSES the "extra chance" proccess.
		//	tile[area_up.ID].base_chance /= tile[area_up.ID].chance_factor;


			accum_int = (1000 * accum); //since the rand() function doesn't accept doubles, I will try to increase accuracy...
			srand(time(NULL));
			chance = rand() % accum_int;
			chance /= 1000;

			for(int i = 0; i > temp_num_custom_tiles; i++)
			{
				if(chance <= chance_accum[i])
					map[mapx][mapy] = tile[i];
			}
			cout << map[mapx][mapy].type_name << "\n";
			mapx++;
		}
		mapx = 0;
		mapy++;
	}

	return;



}