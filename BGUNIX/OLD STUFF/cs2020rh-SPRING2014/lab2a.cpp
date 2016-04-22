// Searching Algorithms
// All code by Addison Snyder
#include <iostream>
#include <iomanip>

using namespace std;

void display(int[], int);
int linear_search(int[], int, int, int&);
int binary_search(int[], int, int, int&);

int main()
{
	const int MAX = 25;
	int num[MAX] = {-7,-2,6,7,8,9,10,13,15,17,22,25,26,27,28,35,37,40,41,42,45,48,50,68,78};
	int key;
	int found;
	int count_l = 0;//counts for linear search computations
	int count_b = 0;//counts for binary
	display(num, MAX);//displays array in formatted manner
	cout << "Enter a number to find in the array: ";
	cin >> key;
	cout << "Performing linear search. . .\n";
	found = linear_search(num, MAX, key, count_l);
	if(found != -1)
		cout << "Found at location " << found << " and it took " << count_l << " comparisons!\n";
	else
		cout << "Number not found! Wasted " << count_l << " comparisons!\n";
	cout << "Performing binary search. . .\n";
	found = binary_search(num, MAX, key, count_b);
		if(found != -1)
		cout << "Found at location " << found << " and it took " << count_b << " comparisons!\n";
	else
		cout << "Number not found! Wasted " << count_b << " comparisons!\n";
	return 0;
}

void display(int num[], int MAX)
{
	int column_length = 5; // length of columns when displaying numbers
	cout << "NUM - ARRAY - MAX = " << MAX << "\n   "; 
	for(int i = 0; i < MAX; i++)
	{
		cout << setw(3) << num[i];
		if((i + 1) % column_length == 0)
			cout << "\n   ";
	}
	cout << "\n";
}

int linear_search(int num[], int MAX, int key, int& count_l)
{
	for(int i = 0; i < MAX; i++)
	{
		count_l += 2;
		if(num[i] == key)// goes through array one element at a time, max computations required equals 2 times the number of elements
		{
			return i;
		}
	}
	return -1;
}

int binary_search(int num[], int MAX, int key, int& count_b)
{
	int left = 0;
	int right = MAX;
	int mid;
	//binary search cuts approx. 50% of the elements off at a time for a cost of 3 computations. Max compuations is equal to 3x if #_elements = 2^x.
	while (left <= right)
	{
		count_b += 3;
		mid = ((right + left)/2);
	if(num[mid] == key)
			return mid;
	if(num[mid] < key)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}
