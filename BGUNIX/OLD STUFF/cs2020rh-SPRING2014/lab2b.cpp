// Addison Snyder
// All code is made by me!
// Sorting Algorithms
#include <iostream>
#include <iomanip>

using namespace std;

void reset(int[], int[]);//initializing functions...
void display(int[]);
void bubblesort(int[], int&, int&, int&);
void selectionsort(int[], int&, int&, int&);

const int MAX = 10000;// SET MAX HERE!!!

int main()
{
	int num[MAX];// <---- ARRAY GOES HERE (IMAGINE BLINKING NEON LIGHTS)
	int backup[MAX];
	int count_b = 0;
	int count_b_passes = 0;
	int count_b_swaps = 0;
	int count_s = 0;
	int count_s_passes = 0;
	int count_s_swaps = 0;

	cout << "Welcome to a sorting program.\n";
	cout << "MAX variable is currently set to " << MAX << ".\n";
	cout << "Setting array to default values. . .\n";
	for(int i = 0; i < MAX; i++)
	{
		cin >> num[i];
		backup[i] = num[i];
	}
	display(num);
	cout << "Performing bubble sort. . .\n";
	bubblesort(num, count_b, count_b_passes, count_b_swaps);
	cout << "Bubble sort was completed for a total of " << count_b << " comparisons from a list of " << MAX << " numbers.\n";
	cout << "Additionally, there were " << count_b_passes << " passes and " << count_b_swaps << " swaps.\n";
	cout << "Resetting array. . .\n";
	reset(num, backup);
	cout << "Performing selection sort. . .\n";
	selectionsort(num, count_s, count_s_passes, count_s_swaps);
	cout << "Selection sort was completed for a total of " << count_s << " comparisons from a list of " << MAX << " numbers.\n";
	cout << "Additionally, there were " << count_s_passes << " passes and " << count_s_swaps << " swaps.\n";
	display(num);
	return 0;
}
void reset(int num[], int backup[])
{
	for(int i = 0; i < MAX; i++)
	{
		num[i] = backup[i];
	}
}

void display(int num[])
{
	int column_length = 20; // length of columns when displaying numbers
	cout << "NUM - ARRAY - MAX = " << MAX << "\n   "; 
	for(int i = 0; i < MAX; i++)
	{
		cout << setw(5) << num[i]; // setw accordingly....
		if((i + 1) % column_length == 0)
			cout << "\n   ";
	}
	cout << "\n";
}

void bubblesort(int num[], int& count_b, 	int& count_b_passes, int& count_b_swaps)
{
	int temp;//temporary area for variable stroage when swapping variables
	bool swap = true; //tells loop swap status and when to stop running. If the loop goes all the way through the array without swapping, loop can stop as the array is sorted.

	while(swap == true)
	{
		count_b++;
		swap = false;
		for(int i = 0; i < (MAX - 1); i++)
		{
		count_b_passes++;
			count_b += 2;
			if(num[i] > num[i + 1])
			{
				count_b_swaps++;
				temp = num[i];//swapping
				num[i] = num[i + 1];
				num[i + 1] = temp;
				swap = true;
			}
		}
	}
}

void selectionsort(int num[], int& count_s, int& count_s_passes, int& count_s_swaps)
{
	int min, minIndex, temp;

	for (int i = 0; i<(MAX - 1); i++)
	{
		count_s++;
		min = num[i];
		minIndex = i;
		for (int j=i+1; j < MAX; j++)
		{
			count_s++;
			count_s_passes++;
			count_s++;
			if (num[j] < min)
			{
				min = num[j];
				minIndex = j;
			}
		}
		count_s++;
		if (min < num[i])
		{
			count_s_swaps++;
			temp = num[i];
			num[i] = min;
			num[minIndex] = temp;
		}
	} 
}
