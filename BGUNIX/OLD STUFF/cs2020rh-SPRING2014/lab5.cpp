//Addison Snyder
//All work is mine
//Pointer lab6
//3/5/14
#include <iostream> 


using namespace std; 
int main ()
{
	//fill array with the numbers 5, 10, 15, 20, 25
	int Grades[] = {5,10,15,20,25};
	int *ptrGrades = Grades;
	//output contents of array using array name and subscript
	for(int i = 0; i < 5; i++)
		cout << "Grade #" << i << ": " << Grades[i] << "\n";
	//output array contents using array name and offset
	for(int i = 0; i < 5; i++)
		cout << "Grade #" << i << ": " << Grades[0 + i] << "\n";
	//point ptrGrades to the beginning of the Grades array
	ptrGrades = &Grades[0];
	//output array contents using a pointer variable without 
	//a subscript and without an offset
	for(int i = 0; i < 5; i++)
		cout << "Grade #" << i << ": " << *ptrGrades++ << "\n";
	//re-set pointer to the beginning of the Grades array
	ptrGrades = &Grades[0];
     //output the array contents using a pointer variable and
     //a subscript
	for(int i = 0; i < 5; i++)
		cout << "Grade #" << i << ": " << ptrGrades[i] << "\n";
	//re-set pointer to the beginning of the Grades array	
	ptrGrades = &Grades[0];	 
	//output the array contents using a pointer variable and 
	//an offset
  	for(int i = 0; i < 5; i++)
		cout << "Grade #" << i << ": " << *(ptrGrades + i) << "\n";      
	return 0; 
}