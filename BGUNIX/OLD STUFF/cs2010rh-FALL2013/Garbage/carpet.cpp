//Addison Snyder

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
double length;
double width;
double area;
double perimeter;
double trim_cost;
double carpet_cost;
double total_cost;

cout << "\n\nPlease enter length of room: ";
cin >> length;
cout << "\nPlease enter width: ";
cin >> width;
cout << "\nHow much $ per square ft? ";
cin >> carpet_cost;
cout << "\nWhat does trim cost per foot? ";
cin >> trim_cost;
perimeter = ((2 * width) + (2 * length));
area = (width * length);

cout << "\nCosts:\nTrim Cost: $" << setprecision(2) << (trim_cost * perimeter);
cout << "\nCarpet Cost: $" << (area * carpet_cost);
cout << "\nTotal Cost: $" <<  << ((area * carpet_cost) + (trim_cost * perimeter));
cout << "\nThanks, and Have a nice day!\n\n\n\n\n\n";

return 0;

}
