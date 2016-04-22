//ADDISON SNYDER

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>
#include "/home/cs/kresman/3270/semaphore/semaphore.h"

using namespace std;

int main ()
{	
	
	Semaphore semaphore(1337, 1);	//creates ONE SEMAPHORE
	semaphore.Init(0, 0);		//initializes semaphore with 0
	
	int pid = fork();//split into 2 proccesses

	const int REPS = 10;	// number of numbers to produce
	
	if(pid == 0)//If child
	{
		srand (time(NULL));// seeds seperateley for child to maintain randomness
		cout << "CHILD ID: " << getpid() << "\n"; // shows child ID
		
		for(int i = 0; i < REPS; i++)
		{
			while(semaphore.ReadValue(0) != 0)	//MAKES SURE THAT EITHER PARENT HAS JUST OUTPUT, OR SEMAPHORE WAS JUST INIT.
				sleep(1);//idles for 1 sec
			cout << "Child produced #" << rand() % 100 << "\n"; // shows child process and random output
			semaphore.Signal(0);//increments semaphore
		}
		exit(1); //kill program
	}
	else// If parent
	{
		cout << "PARENT ID: " << getpid() << "\n";
		for(int i = 0; i < REPS; i++)
		{
			while(semaphore.ReadValue(0) != 1)// WAIT UNTIL CHILD HAS GIVEN OUTPUT
				sleep(1);//wait for a sec			
			cout << "Parent produced #" << rand() % 100 << "\n"; // shows parent process and random output
			semaphore.Wait(0); //decrement semaphore
		}
		semaphore.Destroy(); //destroys the semaphore, so the sysadmin doesn't me.Destroy();
		exit(1);//kill parent
	}
}
