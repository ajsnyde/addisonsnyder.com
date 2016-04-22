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
const int MAP_HEIGHT       = 50;
const int MAP_LENGTH       = 77;
const int CHANCE_FACTOR    = 10000;
////////////////////////////////
const int CHANCE_WOODS     = 500;
const int CHANCE_PLAINS    = 400;
const int CHANCE_WATER     = 300;
const int CHANCE_MOUNTAIN  = 200;
const int CHANCE_CITY      = 500; 
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
	char map_square;
	int color_num = 38;
	int mapcountx = 0;
	int mapcounty = 0;
	char letter = 65; // Start with 'A', moves with graph; along y-axis

	while(mapcounty != MAP_HEIGHT)
	{
		cout << letter << "-";
		while(mapcountx != MAP_LENGTH)
		{
			map_square = map[mapcountx][(MAP_HEIGHT - mapcounty) - 1];
			if(map_square == 'W')
				color_num = 32;
			if(map_square == 'P')
				color_num = 33;
			if(map_square == '~')
				color_num = 34;
			if(map_square == 'C')
				color_num = 35;
			std::cout << "\033" << "[0;" << color_num << "m" << map[mapcountx][(MAP_HEIGHT - mapcounty) - 1]  <<  "\033" << "[0m";
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

	while(mapcounty != MAP_HEIGHT)
	{
		while(mapcountx != MAP_LENGTH)
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
				extra_chance_woods += CHANCE_FACTOR;
			case 'P': 
				extra_chance_plains += CHANCE_FACTOR;				
			case '~': 
				extra_chance_water += (CHANCE_FACTOR * 3);
			case 'M': 
				extra_chance_mountains += CHANCE_FACTOR;
			case 'C': 
				extra_chance_city += (CHANCE_FACTOR * 0.0);
			}
			switch (area_up)
			{
			case 'W': 
				extra_chance_woods += (CHANCE_FACTOR * 1.5);
			case 'P': 
				extra_chance_plains += (CHANCE_FACTOR * 1.5);				
			case '~': 
				extra_chance_water += (CHANCE_FACTOR * 4.5);
			case 'M': 
				extra_chance_mountains += (CHANCE_FACTOR * 1.5);
			case 'C': 
				extra_chance_city += (CHANCE_FACTOR * 0.0);
			}

			// SKYSCRAPER OF CODE!
			chance_total = rand() % (CHANCE_CITY + CHANCE_MOUNTAIN + CHANCE_PLAINS + CHANCE_WATER + CHANCE_WOODS + extra_chance_city + extra_chance_mountains + extra_chance_plains + extra_chance_water + extra_chance_woods);

			if(chance_total >= 0 && chance_total <= (CHANCE_WOODS + extra_chance_woods))
				map[mapcountx][mapcounty] = 'W';
			else if(chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains))
				map[mapcountx][mapcounty] = 'P';
			else if(chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water))
				map[mapcountx][mapcounty] = '~';
			else if(chance_total <= (CHANCE_WOODS + extra_chance_woods + CHANCE_PLAINS + extra_chance_plains + CHANCE_WATER + extra_chance_water + CHANCE_MOUNTAIN + extra_chance_mountains))
				map[mapcountx][mapcounty] = 'M';
			else 
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

