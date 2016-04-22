//Addison Snyder
#include "iostream"
#include "ctime"
#include "cstdlib"

//FUNCTIONS
////////////////////////////////
void  mapgen();
char genterraintype();
void displaymap();
////////////////////////////////

using namespace std;

//GLOBAL CONSTANTS & STUFF
////////////////////////////////
const int MAP_HEIGHT       = 20;
const int MAP_LENGTH       = 40;
const int CHANCE_FACTOR    = 0;
////////////////////////////////
const int CHANCE_WOODS     = 25;
const int CHANCE_PLAINS    = 25;
const int CHANCE_WATER     = 25;
const int CHANCE_MOUNTAIN  = 20;
const int CHANCE_CITY      = 5; 
////////////////////////////////
char map[MAP_LENGTH][MAP_HEIGHT];

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
	cout << "Hello! Welcome to the Map Maker 0.10!\n LET\'S START!\n";
	mapgen();
	displaymap();
	cin >> choice;
	return 0;
}

void displaymap()
{
	int mapcountx = 0;
	int mapcounty = 0;
	char letter = 65; // Start with 'A', moves with graph; along y-axis
	char tile;

	while(mapcounty != MAP_HEIGHT)
	{
		cout << letter << "-";
		while(mapcountx != MAP_LENGTH)
		{
			tile = map[mapcountx][(MAP_HEIGHT - mapcounty) - 1];
			switch (tile)
			{
			case 'W': 
				std::cout << "\033[0;32mW\033[0m";
			case 'P': 
				std::cout << "\033[0;33mP\033[0m";			
			case '~': 
				std::cout << "\033[0;34m~\033[0m";
			case 'M': 
				std::cout << "\033[0;37mM\033[0m";
			case 'C': 
				std::cout << "\033[0;36mC\033[0m";
			default:
				cout << "$";
			}


			mapcountx++;
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

	while(mapcounty != MAP_HEIGHT)
	{
		while(mapcountx != MAP_LENGTH)
		{
			if(mapcountx != 0)
				area_left = map[mapcountx][mapcounty];
			else
				area_left = '-';
			if(mapcounty != 0)
				area_up = map[mapcountx][mapcounty];
			else
				area_up = '-';
			switch (area_left)
			{
			case 'W': 
				extra_chance_woods += CHANCE_FACTOR;
			case 'P': 
				extra_chance_plains += CHANCE_FACTOR;				
			case '~': 
				extra_chance_water += CHANCE_FACTOR;
			case 'M': 
				extra_chance_mountains += CHANCE_FACTOR;
			case 'C': 
				extra_chance_city += CHANCE_FACTOR;
			}
			switch (area_up)
			{
			case 'W': 
				extra_chance_woods += CHANCE_FACTOR;
			case 'P': 
				extra_chance_plains += CHANCE_FACTOR;				
			case '~': 
				extra_chance_water += CHANCE_FACTOR;
			case 'M': 
				extra_chance_mountains += CHANCE_FACTOR;
			case 'C': 
				extra_chance_city += CHANCE_FACTOR;
			}
			// SKYSCRAPER OF CODE!
			chance_total = rand() % (CHANCE_CITY + CHANCE_MOUNTAIN + CHANCE_PLAINS + CHANCE_WATER + CHANCE_WOODS + extra_chance_city + extra_chance_mountains + extra_chance_plains + extra_chance_water + extra_chance_woods);
			if(chance_total >= 0 && chance_total <= (CHANCE_WOODS + extra_chance_woods))
				map[mapcountx][mapcounty] = 'W';
			else if(chance_total > (CHANCE_WOODS + extra_chance_woods) && chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains))
				map[mapcountx][mapcounty] = 'P';
			else if(chance_total > (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains) && chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water))
				map[mapcountx][mapcounty] = '~';
			else if(chance_total > (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water) && chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water + CHANCE_MOUNTAIN + extra_chance_mountains))
				map[mapcountx][mapcounty] = 'M';
			else if(chance_total > (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water + CHANCE_MOUNTAIN + extra_chance_mountains) && chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water + CHANCE_MOUNTAIN + extra_chance_mountains + CHANCE_CITY + extra_chance_city))
				map[mapcountx][mapcounty] = 'C';
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
