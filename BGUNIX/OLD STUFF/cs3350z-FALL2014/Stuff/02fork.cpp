//*******************************************************
//        use of fork                                   *
//*******************************************************


#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[]) {

 int pid;
 pid = fork();
 if (pid == 0) {

        // child 
        cout << "I am the child; my ID" << getpid() << " "<<  
		endl;
        exit(1);
  } 
   
 else{      // 

        cout << " I am the parent; my ID" <<  getpid() << endl;
        cout << " I am the parent; my child ID = " << pid << endl;

 } 
}

/**
bgunix% pwd
/home/cs/kresman/3270
 g++ 02fork.cpp
bgunix% a.out
 I am the parent; my ID23469
 I am the parent; my child ID = 23470
I am the child; my ID23470
*/

