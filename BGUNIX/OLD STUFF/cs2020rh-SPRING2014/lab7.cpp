//Addison Snyder
//lab7.cpp
//Linked Lists
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
struct tile
{
	int ID;
	int color_code;
	int chance;
	tile *next_tile;
};

int get_choice();
void add_tile_front(tile *&first_tile);
void display_tiles(tile *first_tile);
void add_tile_back(tile *&first_tile);
void kill_tile(tile *&first_tile);
void kill_all(tile *&first_tile);
void load_tiles(tile *first_tile);

int main()
{
	int choice = 'X';
	tile *first_tile = NULL;

	choice = get_choice();
	while (choice != 'X')
	{
		if(choice == 'F')
			add_tile_front(first_tile);
		else if(choice == 'R')
			add_tile_back(first_tile);
		else if(choice == 'K')
			kill_tile(first_tile);
		else if(choice == 'V')
			display_tiles(first_tile);
		else if(choice == 'L')
			load_tiles(first_tile);
		else if(choice == 'D')
			kill_all(first_tile);
		choice = get_choice();
	}
	return 0;
}

int get_choice ()
{
	char choice;
	cout << "                       <<< Dread's Tile Creation Kit >>>                       \n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~    F = add tile to Front                                            ~~~~~\n";
	cout << "~~~~~    R = add tile to Rear                                             ~~~~~\n";
	cout << "~~~~~    L = Load tiles                                                   ~~~~~\n";
	cout << "~~~~~    K = Kill tile                                                    ~~~~~\n";
	cout << "~~~~~    D = Destroy all tiles                                            ~~~~~\n";
	cout << "~~~~~    V = View all tiles                                               ~~~~~\n";
	cout << "~~~~~    X = eXit                                                         ~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	cout << "Please enter a selection: ";
	cin >> choice;
	while (choice != 'F' && choice != 'K' && choice != 'V' && choice != 'X' && choice != 'R' && choice != 'L' && choice != 'D')
	{
		cout << "Please enter a VALID selection: ";
		cin >> choice;
	}
	return choice;
}


void add_tile_front(tile *&first_tile)		// add a node
{	
	tile *new_pointer = 0;
	new_pointer = new tile;
	cout << "Enter tile ID: ";
	cin >> new_pointer -> ID;
	cout << "Enter color code: ";
	cin >> new_pointer -> color_code;
	cout << "Enter tile chance: ";
	cin >> new_pointer -> chance;

	new_pointer -> next_tile = 0;

	if (!first_tile) 
		first_tile = new_pointer;
	else
	{   new_pointer->next_tile = first_tile;
		first_tile = new_pointer;
	}
}
void display_tiles(tile *first_tile)		// print the rooms
{	
	tile *position = first_tile;

	if(!position) // checks for list first
		cout << "No tiles have been created!\n";
	else 
    {
		cout << "============================================================\n";
		while(position)//Unless the pointer is NULL, will display next linked struct
		{	cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
			cout << "     ID     -    " << position->ID << "\n";		
			cout << "Color Code  -    " << position->color_code << "\n";
			cout << "   Chance   -    " << position->chance << "\n";
			cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
			position = position->next_tile; // moves to next struct
		}
		cout << "============================================================\n";
	}
}

void load_tiles(tile *first_tile)
{
	ifstream input;
	string file;

	cout << "Please enter a file name: ";
	cin >> file;
	input.open("1.txt");
	if(!input)
	{
		cout << "File cannot be opened!\n";
		return;
	}
	else
	{

		cout << "Loading. . .\n";
		int counter = 0;//no need to make a counter up top if there is a possibility it won't be used...

		tile *tptr = NULL;			// Can we do this differently?!?!?!?!?
		tile *new_pointer = NULL;
		while(!input.eof())
		{
			new_pointer = new tile;
			input >> new_pointer -> ID; 
			input >>  new_pointer -> color_code; 
			input >> new_pointer -> chance;
			new_pointer -> next_tile = NULL;
			if(!first_tile)//if this is the only struct, there isn't a need to link
				first_tile = new_pointer;
			else 
			{
				tptr = first_tile;
				while(tptr->next_tile)//if not, it is linked to the back (the first struct with a null node)
					tptr = tptr->next_tile;
				tptr -> next_tile = new_pointer;
			}
			counter++;
		}
		cout << counter << " tiles were loaded.\n";
		return;
	}
}

void add_tile_back(tile *&first_tile)		// Adding nodes to the end of the list
{	
	tile *tptr = NULL;			// Can we do this differently?!?!?!?!?
	tile *new_pointer = NULL;

	new_pointer = new tile; //create a new struct...
	cout << "Please enter ID: ";
	cin >> new_pointer -> ID; 
	cout << "Please enter color code: ";
	cin >>  new_pointer -> color_code; 
	cout << "Please enter chance: ";
	cin >> new_pointer -> chance;

	new_pointer->next_tile = NULL;//and makes sure the pointer is NULL.

	if(!first_tile)//if this is the only struct, there isn't a need to link
		first_tile = new_pointer;
	else
	{
		tptr = first_tile;
		while(tptr->next_tile)//if not, it is linked to the back (the first struct with a null node)
			tptr = tptr->next_tile;
		tptr->next_tile = new_pointer;
	}
}

void kill_tile(tile *&first_tile)
{
	tile *nodePtr;
	tile *previousNode;
	int targetid;

	cout << "Please enter tile ID:";
	cin >> targetid;

	if (!first_tile)//can't destroy what isn't there. Still working on advances in that department, though...
	{  
		cout << "Unfortunately, the list is empty.\n";
		return; //returns nothing
	}
	if (first_tile->ID == targetid)//checks first tile only
	{
		nodePtr = first_tile->next_tile;
		delete first_tile;
		first_tile = nodePtr;
		cout << "Tile #" << targetid << " has been terminated...\n";
	}
	else
	{
		nodePtr = first_tile;

		while (nodePtr != NULL && nodePtr->ID != targetid)//then goes through list
		{  
			previousNode = nodePtr;
			nodePtr = nodePtr->next_tile;
		}

		if (nodePtr)
		{
			previousNode = 0;
			previousNode->next_tile = nodePtr->next_tile;
			delete nodePtr;
			cout << "Tile #" << targetid << " has been terminated...\n";
		}
		else
			cout << "Can't find ID. Check under the couch.\n";
	}
}
void kill_all(tile *&first_tile)
{
	tile *node;
	tile *next;

	node = first_tile;

	while (node)
	{
		next = node->next_tile;
		delete node;
		node = next;
	}
	first_tile = NULL;
	cout << "All tiles are destroyed.\n";
}