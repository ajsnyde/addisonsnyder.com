/************************************************************************
 * 		Demonstrate use of Semaphores
 ************************************************************************

     Play with semaphore creation/use/destruction, etc

     Uses instructor supplied 'class' and its member functions 
 	(Available as semaphore.o file - NO source given!)

     Semaphore abc (5678, 3); //create 3 semaphores, some unique KEY 5678
                              //OS creates a semaphore group  
			      //with a unique ID under your username

     abc.Init(2, 5);          //initialize 3rd semaphore to value 5
     abc.Wait(2);             //down 3rd by 1
     abc.Signal(0);           //up 1st by 1
     abc.Destroy();           //destroy all (5) semaphores

Some useful unix commands 

     ipcs                     //see info on shared memory and semaphores
     ipcrm -s 14              //remove all semaphores with ID 14


 ***********************************************************************/



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
using namespace std;

int main (int argc,char *argv[]) {

	cout << "Hello world, create 2 semaphores... " << endl;

        //create semaphore, some unique key 1234, with 2 semaphores
	Semaphore sem(1234, 2); 
        sleep(5);
	
	sem.Init(0, 1); //initialize 1st semaphore to 1

	sem.Init(1, 4); //initialize 2nd semaphore to 4

	sem.Signal(0);  //up 1st semaphore by 1

	sem.Wait(1);    //down 2nd semaphore by 1

	cout << "First @ 2, second @ 3 ... " << endl;

	sem.Destroy();  //destroy ALL (both) semaphores!
}

/**

	SHOWS program running in background, output of ipcs etc

$ g++ semaphoreDriver.cpp  /home/cs/kresman/3270/semaphore/semaphore.o

$ ipcs
IPC status from <running system> as of Tue Sep 30 15:13:23 EDT 2014
T         ID      KEY        MODE        OWNER    GROUP
Message Queues:
Shared Memory:
m         13   0x741cc1a3 --rw-rw-rw-     root     root
m         12   0x741cc1a2 --rw-rw-rw-     root     root
m         11   0x741cc1a1 --rw-rw-rw-     root     root
m         10   0x741cc1a0 --rw-rw-rw-     root     root
m          0   0x435dce60 --rw-rw-rw-     root     root
Semaphores:


$ a.out &
[1] 1539
Hello world, create 2 semaphores...

$ipcs
IPC status from <running system> as of Tue Sep 30 15:13:31 EDT 2014
T         ID      KEY        MODE        OWNER    GROUP
Message Queues:
Shared Memory:
m         13   0x741cc1a3 --rw-rw-rw-     root     root
m         12   0x741cc1a2 --rw-rw-rw-     root     root
m         11   0x741cc1a1 --rw-rw-rw-     root     root
m         10   0x741cc1a0 --rw-rw-rw-     root     root
m          0   0x435dce60 --rw-rw-rw-     root     root
Semaphores:
s         14   0x4d2      --ra-ra-ra-  kresman     user

First @ 2, second @ 3 ...

[1]+  Done                    a.out


$ ipcs
IPC status from <running system> as of Tue Sep 30 15:13:36 EDT 2014
T         ID      KEY        MODE        OWNER    GROUP
Message Queues:
Shared Memory:
m         13   0x741cc1a3 --rw-rw-rw-     root     root
m         12   0x741cc1a2 --rw-rw-rw-     root     root
m         11   0x741cc1a1 --rw-rw-rw-     root     root
m         10   0x741cc1a0 --rw-rw-rw-     root     root
m          0   0x435dce60 --rw-rw-rw-     root     root
Semaphores:
$

*/
