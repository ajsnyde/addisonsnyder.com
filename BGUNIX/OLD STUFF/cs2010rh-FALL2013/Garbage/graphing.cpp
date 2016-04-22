#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


int main()
{
	int count = 0;  //used for getting y-axis values
	int count1 = 0; //counter for asking values on "stats" numbers
	int count2 = 0; //counter used for finding max/(min?)
	int count3 = 0; //used for grapgh initialization
	int count4 = 0; //also used in nested loop
	int max = -1524;
	int min = -1524;
	const int HEIGHT = 10;//indicates graph height
	const int LENGTH = 30;//and length
	const int SIZE = 10; //determines size of horizontal graph
	char graph[LENGTH][HEIGHT];
	char background;
	int y_axis[HEIGHT];
	int stats[SIZE] = {0,0,0,0,0,0,0,0,0,0};//initialize all as 0, and for future reference

	//WELCOME
	cout << "Welcome to Dread's Graphing Utility 1.0!\n";

	while (count1 != SIZE)
	{
		cout << "Enter number #" << (count1 + 1) << ": ";
		cin >> stats[count1];
		count1++;
	}
	while(count2 != SIZE)
	{
		if(stats[count2] >= max || max == -1524)
			max = stats[count2];
		if(stats[count2] <= min || min == -1524)
			min = stats[count2];
		count2++;
	}

	cout << "\nMin: " << min;
	cout << "\nMax: " << max;
	cout << "\n";

	//y-axis values
	while(count != HEIGHT)
	{
		y_axis[count] = ((((max - min)/HEIGHT) * count) + min);
		count++;
	}

	//initialize graph
	cout << "Please enter a char for the background of the graph(- for spaces): ";
	cin >> background;
	if (background == '-')
		background = ' ';
	while(count3 != LENGTH)
	{
		while(count4 != HEIGHT)
		{
			graph[count3][HEIGHT - count4] = background;
			count4++;
		}
	count3++;
	count4 = 0;
	}
	
	count2 = 0;
	while(count2 != 10)
	{
		graph[((stats[HEIGHT - 1]))][LENGTH - count2] = '-';
		count2++;
		//((((max - min)/HEIGHT) * count) + min)
	}


	cout << "\n\n   GRAPH:\n\n";
	count3 = 0;
	while(count3 != HEIGHT)
	{
	cout << setw(5) << y_axis[((HEIGHT - count3) - 1)] << "\\_|";
		while(count4 != LENGTH)
		{
			cout << graph[count3][count4];
			count4++;
		}
	cout << "\n";
	count3++;
	count4 = 0;
	}
	count3 = 0;
	cin >> count1;


	return 0;
}

