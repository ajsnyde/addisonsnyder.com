#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdbool.h>

using namespace std;

int main ()
{
	
	int childread[1], parentread[1], childwrite[1], parentwrite[1]; // used to hold data along pipe
	int one[2], two[2]; // pipe read/write indicators
	pipe(one); // 0 is read, 1 is write
	pipe(two); // 0 is read, 1 is write
	
	int pid = fork();//split into 2 proccesses

	const int REPS = 10;	// number of numbers to produce
	
	if(pid == 0)//If child
	{
		close(two[1]);
		close(one[0]);		srand (time(NULL));// seeds seperateley for child to maintain randomness
		cout << "CHILD ID: " << getpid() << "\n"; // shows child ID
		
		for(int i = 0; i < REPS; i++)
		{
			childwrite[0] = 1;
			read(two[0], parentread, 1); // syncs program
			write(one[1], childwrite, 1); // writes one number to create a round robin setup
			cout << "Child produced #" << rand() % 100 << "\n"; // shows child process and random output
		}
		close(two[0]);
		close(one[1]);
		exit(1);
	}
	else// If parent
	{
		cout << "PARENT ID: " << getpid() << "\n";
		close(two[0]);
		close(one[1]);
		for(int i = 0; i < REPS; i++)
		{
			parentwrite[0] = 1;
			write(two[1], parentwrite, 1);
			read(one[0], childread, 1); // gets 'ready' from child
			cout << "Parent produced #" << rand() % 100 << "\n"; // shows parent process and random output
		}
		close(two[1]);
		close(one[0]);
		exit(1);
	}
}
