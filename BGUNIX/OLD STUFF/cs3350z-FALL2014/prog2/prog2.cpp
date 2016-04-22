#include "iostream"
#include "string"
#include "vector"
#include "todo.h"

using namespace std;

void add(todo, vector<todo>&);
void del(int, vector<todo>&);
void disp(vector<todo>&);

int main()
{
	char choice = '0';	//SEED CHOICE
	string info;
	int priority;
	vector<todo> list;

	cout << "Welcome to the To-Do List Program!\n";

	while(choice != 'X')	//MENU SYSTEM
	{
		cout << "   A = ADD ITEM\n   D = DELETE ITEM\n   P = PRINT ITEMS\n   X = EXIT\n   INPUT: ";
		cin >> choice;
		switch (choice)
		{
		case 'A':	//ADD
			cout << "Please enter priority number: ";
			cin >> priority;
			cin.ignore();
			cout << "Please enter description: ";
			getline(cin, info);	//GETLINE ALLOWS SPACE CHARS IN STRING
			add(todo(priority, info), list);
			cout << "Item has been added!\n";
			break;
		case 'D':	//DELETE
			cout << "Please enter priority number of item to be deleted: ";
			cin >> priority;
			del(priority, list);
			cout << "Done!\n";
			break;
		case 'P':	//PRINT
			cout << "Displaying To-Do list:\n~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			disp(list);
			break;
		case 'X':	//EXIT
			cout << "Exiting. . .\n";
			break;
		default:
			cout << "Please enter a valid option!\n";
		}
	}
	return 0;
}

/* ALTERNATIVE ADD FUNCTION - COPIES VECTOR AND ADDS ONE EXTRA ELEMENT TO ITS CORRESPONDING SPOT
void add(todo in, vector<todo> &out)
{
	vector<todo> temp_list;
	int i;
	int priority = in.get_priority();

	for(i = 0; i < out.size(); i++)
	{
		if(out[i].get_priority() < priority)
			temp_list.push_back(out[i]);
		else
		{
			temp_list.push_back(in);
			temp_list.push_back(out[i]);
		}
	}
	if(temp_list.size() == out.size())
		temp_list.push_back(in);
	out = temp_list;
}
*/

void add(todo in, vector<todo> &out)	//INSERTS ITEM IN ITS CORRECT ORDER
{
	vector<todo>::iterator it;
	unsigned int i = 0;
	int priority = in.get_priority();

	for(it = out.begin(); it != out.end(); it++, i++)	//INSERTS USING INSERT FUNCTION
	{
		if(out[i].get_priority() >= priority)
			break;
	}
	out.insert(out.begin() + i, in);
	return;
}

void del(int rank, vector<todo> &out)	//DELETES THE FIRST ITEM WITH THE PASSED PRIORITY NUMBER
{
	vector<todo> temp_list;
	unsigned int i;	//UNSIGNED TO STOP THOSE ANNOYING WARNINGS FROM COMPILER
	bool del = false;

	for(i = 0; i < out.size(); i++)
	{
		if(out[i].get_priority() == rank && !del)	//ENSURES THAT ONLY ONE ITEM IS DELETED USING del bool
			del = true;
		else
		{
			temp_list.push_back(out[i]);
		}
	}
	out = temp_list;
}

void disp(vector<todo> &out)	//DISPLAYS ALL todos IN THE PASSED VECTOR
{
	for(unsigned int i = 0; i < out.size(); i++)
		out[i].display();
}
