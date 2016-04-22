#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>           /* c++ I/O headers */
using namespace std;

int main (int argc, char *argv[]) {
 char childWritesToPipe[512], parentReadsFromPipe[512];
 int pid, pipeName[2], index, count;

 pipe (pipeName);  /* [0] is 'read' end; [1] is 'write' end */
 pid = fork();

 if (pid == 0) {

        /* child */
        cout << "I am the child; my ID" << getpid() << " "<<  endl;
        cout << "Please enter your first name" << endl;

        cin >> childWritesToPipe;       // read from the terminal window
        cout << "Child  printing..."
                << childWritesToPipe << endl; // print to term window

        close (pipeName[0]);    //I don't read off of pipe
        write (pipeName[1], childWritesToPipe, strlen(childWritesToPipe));
        close (pipeName[1]);    //all done with writing
        exit(1);

  }

 else{      /* parent */
        cout << "I am the parent; my ID = " << getpid() << endl;
        close (pipeName[1]);    //I don't  write to pipe

        count = read (pipeName[0], parentReadsFromPipe, 512);
        cout << "parent printing..." ;
        for (index=0; index < count; index++)
                cout << parentReadsFromPipe[index] ;
        cout << endl;

        close (pipeName[0]);    //all done with reading



 }
}
