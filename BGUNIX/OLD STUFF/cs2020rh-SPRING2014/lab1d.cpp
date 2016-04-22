// All code by Addison Snyder
// Name Program
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int num_students;
	string name;
	string low = "AAA";
	string high = "ZZZ";


	
	while(num_students < 1 || num_students > 25)
	{
	cout << "Enter the # of students (must be between 1 and 25): ";
	cin >> num_students;
	}

	for(int i = 0; i != num_students; i++)
	{
		cout << "Enter student #" << (i + 1) << ": ";
		cin >> name;
		if(name > low)
			low = name;
		if(name < high)
			high = name;
	}
	cout << "First: " << high << "\n";
	cout << "Last: " << low << "\n";
	return 0;
}

