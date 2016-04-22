//Addison Snyder
#include "iostream"
#include "ctime"
#include "cstdlib"



//Changes from version 0.11 include:
//
//Many global constants are now global variables (temporary)
//Added questions for map seeding (mapstats function)
//         12/10/13

//FUNCTIONS
////////////////////////////////
void  mapgen();
char genterraintype();
void displaymap();
void mapstats();
////////////////////////////////

using namespace std;

//GLOBAL CONSTANTS & STUFF
////////////////////////////////
const int map_height       = 50;
const int map_length       = 77;
int base_chance_factor    = 2000;
double chance_factor_woods = 1;
double chance_factor_plains = 1;
double chance_factor_water = 1;
double chance_factor_mountains = 1;
double chance_factor_city = 1;
////////////////////////////////
int chance_woods     = 500;
int chance_plains    = 500;
int chance_water     = 800;
int chance_mountain  = 50;
int chance_city      = 50; 
////////////////////////////////
char map[map_length][map_height];

int extra_chance_woods     = 0;
int extra_chance_plains    = 0;
int extra_chance_water     = 0;
int extra_chance_mountains = 0;
int extra_chance_city      = 0;
int chance = 0;

int choice;


int main()
{
	srand(time(NULL));
	cout << "Hello! Welcome to the Map Maker 0.12!\n LET\'S START!\n";
	mapstats();
	mapgen();
	displaymap();
	cin >> choice;
	return 0;
}

void mapstats()
{
	cout << "Okay, time for map attributes!\n";

	cout << "Please enter the chance factor (how much adjacent tiles affect tile generation; must be integer): ";
	cin >> base_chance_factor;
	cout << "When determining tiles, the chance factor is multiplied by a TERRAIN-SPECIFIC chance factor. This allows certain tiles to dominate the map in meaningful ways. For example, increasing water's chance factor (ex. 1.67) yields oceans. Keep in mind that all of these values are relative to one another.\n";
	cout << "Please enter chance factor for WOODS: ";
	cin >> chance_factor_woods;
	cout << "Please enter chance factor for PLAINS: ";
	cin >> chance_factor_plains;
	cout << "Please enter chance factor for WATER: ";
	cin >> chance_factor_water;
	cout << "Please enter chance factor for MOUNTAINS: ";
	cin >> chance_factor_mountains;
	cout << "Please enter chance factor for CITIES: ";
	cin >> chance_factor_city;
	cout << "Next up is the base chance. This determines the base chance of a tile occuring. With a chance factor of zero, these values would yeild specific proportions of terrains. (must be integer)\n";
	cout << "Please enter the base chance for WOODS: ";
	cin >> chance_woods;
	cout << "Please enter the base chance for PLAINS: ";
	cin >> chance_plains;
	cout << "Please enter the base chance for WATER: ";
	cin >> chance_water;
	cout << "Please enter the base chance for MOUNTAINS: ";
	cin >> chance_mountain;
	cout << "Please enter the base chance for CITIES: ";
	cin >> chance_city;
	
}

void displaymap()
{
	char map_square;
	int color_num = 38;
	int mapcountx = 0;
	int mapcounty = 0;
	char letter = 65; // Start with 'A', moves with graph; along y-axis

	while(mapcounty != map_height)
	{
		cout << letter << "-";
		while(mapcountx != map_length)
		{
			map_square = map[mapcountx][(map_height - mapcounty) - 1];
			if(map_square == 'W')
				color_num = 32;
			if(map_square == 'P')
				color_num = 33;
			if(map_square == '~')
				color_num = 34;
			if(map_square == 'C')
				color_num = 35;
			std::cout << "\033" << "[0;" << color_num << "m" << map[mapcountx][(map_height - mapcounty) - 1]  <<  "\033" << "[0m";
			mapcountx++;
			color_num = 38;
		}
		cout << "\n";
		mapcountx = 0;
		mapcounty++;
		letter++;
	}
}


void mapgen()
{
	int mapcounty = 0;
	int mapcountx = 0;
	int chance_total = 0;
	char area_left;
	char area_up;

	while(mapcounty != map_height)
	{
		while(mapcountx != map_length)
		{
			extra_chance_woods     = 0;
			extra_chance_plains    = 0;
			extra_chance_water     = 0;
			extra_chance_mountains = 0;
			extra_chance_city      = 0;
			if(mapcountx != 0)
				area_left = map[(mapcountx - 1)][mapcounty];
			else
				area_left = '-';
			if(mapcounty != 0)
				area_up = map[mapcountx][(mapcounty - 1)];
			else
				area_up = '-';
			switch (area_left)
			{
			case 'W': 
				extra_chance_woods += (base_chance_factor * chance_factor_woods);
			case 'P': 
				extra_chance_plains += (base_chance_factor * chance_factor_plains);				
			case '~': 
				extra_chance_water += (base_chance_factor * chance_factor_water);
			case 'M': 
				extra_chance_mountains += (base_chance_factor * chance_factor_mountains);
			case 'C': 
				extra_chance_city += (base_chance_factor * chance_factor_city);
			}
			switch (area_up)
			{
			case 'W': 
				extra_chance_woods += (base_chance_factor * chance_factor_woods);
			case 'P': 
				extra_chance_plains += (base_chance_factor * chance_factor_plains);				
			case '~': 
				extra_chance_water += (base_chance_factor * chance_factor_water);
			case 'M': 
				extra_chance_mountains += (base_chance_factor * chance_factor_mountains);
			case 'C': 
				extra_chance_city += (base_chance_factor * chance_factor_city);
			}

			// SKYSCRAPER OF CODE!
			chance_total = rand() % (chance_city + chance_mountain + chance_plains + chance_water + chance_woods + extra_chance_city + extra_chance_mountains + extra_chance_plains + extra_chance_water + extra_chance_woods);

			if (chance_total <= (chance_city + extra_chance_city))
				map[mapcountx][mapcounty] = 'C';
			else if (chance_total <= (chance_city + extra_chance_city + chance_mountain + extra_chance_mountains))
				map[mapcountx][mapcounty] = 'M';
			else if (chance_total <= (chance_city + extra_chance_city + chance_mountain + extra_chance_mountains + chance_woods + extra_chance_woods))
				map[mapcountx][mapcounty] = 'W';
			else if (chance_total <= (chance_city + extra_chance_city + chance_mountain + extra_chance_mountains + chance_woods + extra_chance_woods + chance_plains + extra_chance_plains))
				map[mapcountx][mapcounty] = 'P';
			else 
				map[mapcountx][mapcounty] = '~';

			extra_chance_woods     = 0;
			extra_chance_plains    = 0;
			extra_chance_water     = 0;
			extra_chance_mountains = 0;
			extra_chance_city      = 0;

			mapcountx++;
		}


		mapcountx = 0;
		mapcounty++;
	}

	return;
}

