/********************************************************
*       Working with command line arguments             *
*       This program copies a file prints command line  *
*       arguments.                                      *

*     Usage: programnamfile  arg1 arg2 arg3 ...         *
********************************************************/

#include <stdio.h>
#include  <iostream>
#include <unistd.h>

using namespace std;


int main (int argc, char *argv[])
{
int index;

  cout <<"program name is " <<  argv[0] << endl;
  for (index = 1; index < argc; index ++) {
        cout <<"(Next) Arg is " <<  argv[index] << endl;

  }

}

/**
bgunix% photo
Enter name of log file:  screenCapture
Use CTRL-d to terminate recording
Script started, file is screenCapture
sh-3.00$hostname
bgunix
sh-3.00$ pwd
/home/cs/3270

sh-3.00$ g++ 01arg.cpp
sh-3.00$ a.out 123 456 "hello world"
program name is a.out
(Next) Arg is 123
(Next) Arg is 456
(Next) Arg is hello world
sh-3.00$ exit
exit
Script done, file is screenCapture
bgunix% cat screenCapture
Script started on 
sh-3.00$ g++ 01arg.cpp
sh-3.00$ a.out 123 456 "hello world"
program name is a.out
(Next) Arg is 123
(Next) Arg is 456
(Next) Arg is hello world
sh-3.00$ exit
exit

script done on 

*/
