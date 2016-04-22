#include "iostream"
#include "string"
#include "Car.h"
#include "List.h"

using namespace std;

int main()
{
	List Lot;
	Lot.add("Dodge", "Dakota", "Silver", "819234DHS8235", "N/A", 2001, 99458, 1200, 0);
	Lot.displaylist();
	Lot.load(Lot);
	Lot.displaylist();
	return 0;
}

