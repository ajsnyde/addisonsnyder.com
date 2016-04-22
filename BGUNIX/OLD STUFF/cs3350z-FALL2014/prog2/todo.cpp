#include "todo.h"
#include "iostream"
#include "vector"

using namespace std;

todo::todo(void)	//DEFAULT CONSTRUCTOR
{
	set_id(-1);
	set_priority(-1);
	set_info("uninitialized");
}

todo::todo(int a, string b)	//OVERLOADED CONSTRUCTOR
{
	set_id(-1);
	set_priority(a);
	set_info(b);
}

int todo::get_id()	//BASIC GETTERS AND SETTERS
{
	return id;
}

int todo::get_priority()
{
	return priority;
}

string todo::get_info()
{
	return info;
}

void todo::set_id(int new_id)
{
	id = new_id;
}

void todo::set_priority(int new_priority)
{
	priority = new_priority;
}

void todo::set_info(string new_info)
{
	info = new_info;
}

void todo::display()	//DISPLAYS PROPERTIES
{
	cout << info << " - Priority: " << priority << "\n";
}
