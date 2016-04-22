#include "iostream"
#include "List.h"

using namespace std;

/////////////////////////////////
//Standard constructor, forces head to start out NULL
/////////////////////////////////

List::List()
{
	head = NULL;
}

////////////////////////////////
//Destructor
////////////////////////////////

List::~List()
{
}

////////////////////////////////
//Adds cars to the end of list
////////////////////////////////

void List::addcar()
{
	if(head == NULL)
		head = new Car();
	else
	{
		Car *node;
		node = head;
		while(node->next != NULL)
			node = node->next;
		node->next = new Car();
	}
}

//////////////////////////////////
//inserts a car. num is beginning number. i.e. if there were 3 cars and num is 2, the new car will be between 2 and 3.
//////////////////////////////////

void List::insertcar(int num)
{
	if(num < 0)
	{
		cout << "Cannot insert car. Number out of range!\n";
		return;
	}
	if(head == NULL)
		head = new Car();
		else
	{
		Car *node;
		node = head;
		for(int i = 0; i < num; i++)
		{
			if(node->next == NULL)
			{
				cout << "Out of range!\n";
				return;
			}
			else
				node = node->next;
		}
		node->next = new Car();
		cout << "Created new car on spot " << num+1 << "\n";
	}
}
////////////////////////////////////
//destroys car #num
////////////////////////////////////
void List::killcar(int num)
{
	if(num < 0)
	{
		cout << "Cannot insert car. Number out of range!\n";
		return;
	}
	if(head == NULL)
		head = new Car();
		else
	{
		Car *node;
		node = head;
		for(int i = 0; i < num; i++)
		{
			if(node->next == NULL)
			{
				cout << "Out of range!\n";
				return;
			}
			else
				node = node->next;
		}
		Car* temp;
		temp = node->next->next;
		delete node->next;
		node->next = temp;
		cout << "Deleted car on spot " << 1 << "\n";
	}
}
/////////////////////////////////
//Displays all cars using display() from Car class
/////////////////////////////////
void List::displayall()
{
	if(head == NULL)
	{
		cout << "No cars!\n";
		return;
	}
	Car* counter;
	counter = head;
	for(int i = 1; counter->next != NULL; i++)
	{
		cout << "Car #" << i << "\n";
	(*counter).display();
	counter = counter->next;
	}
	(*counter).display();
}

//////////////////////////////////
//returns the pointer of car #num
//////////////////////////////////


Car* List::getcar(int num)
{
	Car *counter = head;
		for(int i = 0; i < num; i++)
	{
		if(counter->next == NULL)
		{
			cout << "Out of range!\n";
			return head;
		}
		else
			counter = counter->next;
	}
		return counter;
}