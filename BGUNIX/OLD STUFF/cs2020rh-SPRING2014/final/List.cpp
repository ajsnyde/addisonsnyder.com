#include "iostream"
#include "List.h"
#include "fstream"

using namespace std;

List::List(void)
{
	head = NULL;
}

List::List(const List &obj)
{
	Car *IN;
	string tempmake;
	string tempmodel;
	string tempcolor;
	string tempVIN;
	string temptag;
	int tempyear;
	int tempmileage;
	int tempvalue;
	bool tempNEW;
	IN = obj.head;
	tempmake = IN->make;
	tempmodel = IN->model;
	tempcolor = IN->color;
	tempVIN = IN->VIN;
	temptag = IN->tag;
	tempyear = IN->year;
	tempmileage = IN->mileage;
	tempvalue = IN->value;
	tempNEW = IN->NEW;
	head = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW);

	while(IN->next != NULL)
	{
		IN = IN->next;
		tempmake = IN->make;
		tempmodel = IN->model;
		tempcolor = IN->color;
		tempVIN = IN->VIN;
		temptag = IN->tag;
		tempyear = IN->year;
		tempmileage = IN->mileage;
		tempvalue = IN->value;
		tempNEW = IN->NEW;
		head = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW, head);
	}
}

const List List::operator=(const List &right)
{
	Car *car_ptr, *next_car;

	car_ptr = head;
	while(car_ptr != NULL)
	{
		next_car = car_ptr->next;
		delete car_ptr;
		car_ptr = next_car;
	}

	string tempmake;
	string tempmodel;
	string tempcolor;
	string tempVIN;
	string temptag;
	int tempyear;
	int tempmileage;
	int tempvalue;
	bool tempNEW;

	car_ptr = right.head;
	tempmake = car_ptr->make;
	tempmodel = car_ptr->model;
	tempcolor = car_ptr->color;
	tempVIN = car_ptr->VIN;
	temptag = car_ptr->tag;
	tempyear = car_ptr->year;
	tempmileage = car_ptr->mileage;
	tempvalue = car_ptr->value;
	tempNEW = car_ptr->NEW;
	head = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW);

	while(car_ptr->next != NULL)
	{
		car_ptr = car_ptr->next;
		tempmake = car_ptr->make;
		tempmodel = car_ptr->model;
		tempcolor = car_ptr->color;
		tempVIN = car_ptr->VIN;
		temptag = car_ptr->tag;
		tempyear = car_ptr->year;
		tempmileage = car_ptr->mileage;
		tempvalue = car_ptr->value;
		tempNEW = car_ptr->NEW;
		head = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW, head);
	}
	return *this;
}

void List::add(string tempmake, string tempmodel, string tempcolor, string tempVIN, string temptag, int tempyear, int tempmileage, int tempvalue, bool tempNEW)
{
	if(head == NULL)
		head = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW, NULL);
	else
	{
		Car *car_ptr;
		car_ptr = head;
		while(car_ptr->next != NULL)
			car_ptr = car_ptr->next;
		car_ptr->next = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW, NULL);
	}
}

void List::displaylist()
{
	Car *car_ptr;
	int i = 1;
	string word;
	string number;
	car_ptr = head;
	if(car_ptr == NULL)
	{
		cout << "No cars to be displayed!\n";
		return;
	}
	while(car_ptr != NULL)
	{
		cout << "~~~~~~~~~~~~~~ Car #" << i << " ~~~~~~~~~~~~~~~~~~\n";
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "Make:       " << car_ptr->make << "\n";
		cout << "Model:      " << car_ptr->model << "\n";
		cout << "Year:       " << car_ptr->year << "\n";
		cout << "Color:      " << car_ptr->color << "\n";
		cout << "VIN:        " << car_ptr->VIN << "\n";
		cout << "Dealer Tag: " << car_ptr->tag << "\n";
		cout << "Mileage:    " << car_ptr->mileage << "\n";
		cout << "Value:      $" << car_ptr->value << "\n";
		cout << "Condition:  ";
		if(car_ptr->NEW)
			cout << "NEW\n";
		else
			cout << "USED\n";
		car_ptr = car_ptr->next;
		i++;
	}
}


void List::ins(int num, string tempmake, string tempmodel, string tempcolor, string tempVIN, string temptag, int tempyear, int tempmileage, int tempvalue, bool tempNEW) 
{
	Car *car_ptr, *previous_car; 
	int i = 0;
	previous_car = NULL;
	car_ptr = NULL;
	if(head == NULL)
	{
		add(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW);
		return;
	}
	else
	{
		previous_car = head;
		car_ptr = head->next;
		while (car_ptr != NULL &&  i != num)
		{
			previous_car = car_ptr; 
			car_ptr = car_ptr->next;
			i++;
		}
	}
	previous_car->next = new Car(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW, car_ptr);
}
void List::del(int num) 
{
	Car *car_ptr, *previous_car;
	previous_car = NULL;
	int i = 0;
	if (head == NULL)
	{
		cout << "No cars detected!\n";
		return;
	}

	if (i == num)
	{
		car_ptr = head;
		head = head->next;
		delete car_ptr;
		cout << "Car #" <<  (i + 1) << " was successfully deleted!\n";
	}
	else
	{
		car_ptr = head;
		while (car_ptr != NULL && i != num)
		{
			previous_car = car_ptr; car_ptr = car_ptr->next;
			i++;
		}
		if(car_ptr)
		{
			previous_car->next = car_ptr->next;
			delete car_ptr;
			cout << "Car #" <<  (i + 1) << " was successfully deleted!\n";
		}
	}
}

void List::load(List list)
{
	ifstream input;
	string file;
	string tempmake;
	string tempmodel;
	string tempcolor;
	string tempVIN;
	string temptag;
	int tempyear;
	int tempmileage;
	int tempvalue;
	bool tempNEW;
	cout << "Please enter file name: ";
	cin >> file;
		input.open("lot.txt");
	cout << "Loading " << file << ". . .\n";
	while(!input)
	{
		cout << "File not found! Please reenter name (X to abort): ";
		cin >> file;
		input.open("lot.txt");
		if(file == "X")
			return;
	}
	int i = 1;
	while(!input.eof())
	{
		cout << "Entering car #" << i++ << "\n";
		input >> tempmake;
		input >> tempmodel;
		input >> tempcolor;
		input >> tempVIN;
		input >> temptag;
		input >> tempyear;
		input >> tempmileage;
		input >> tempvalue;
		input >> tempNEW;
		add(tempmake, tempmodel, tempcolor, tempVIN, temptag, tempyear, tempmileage, tempvalue, tempNEW);
	}
}

List::~List()
{
	Car *car_ptr, *next_car;
	car_ptr = head;
	while(car_ptr != NULL)
	{
		next_car = car_ptr->next;
		delete car_ptr;
		car_ptr = next_car;
	}
}

