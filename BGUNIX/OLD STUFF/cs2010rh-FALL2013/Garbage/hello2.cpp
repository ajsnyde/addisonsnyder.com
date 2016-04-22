//random program 9/16/13

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string username;
	int user_age;

cout << "Enter your age: ";
cin >> username;
cout << "\nPlease enter your age: ";
cin >> user_age;

//output: display message to user
cout << "Hello, " << username << "!" << endl;
cout << "You are " << user_age << " years old." << endl;

return 0;
}
