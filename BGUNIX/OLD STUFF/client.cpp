///////////////////////////////////////////
// Addison Snyder
// CS 3270 Kresman
///////////////////////////////////////////

#include <iostream>
#include "clientServer.h"
#include <sys/types.h>
#include <sys/socket.h>

int connectToHost (int , char * , int );
void append(char *, char);


using namespace std;

int main(int argc, char* argv[])
{
	int socketNO, connect, n, done;
	cout << "Entered server: " << argv[1] << "\n\n";	// takes second argument (1st is program name) and accepts as server address
	char *serv = argv[1];
	char buffer[128] = "";					// outgoing buffer for command line arguments (names to send to finger server)
	char in[256];						// input buffer for messages recieved from finger server

	socketNO = socket(AF_INET, SOCK_STREAM, 0);		// sets up The socket connection (streaming, no flags)

	connect = connectToHost(socketNO, serv, 79);		// connects to server using supplied address
	if(connect != 0)
		cout << "Error code " << connect << "!\n";	// basic error reaction
	else
		cout << "Connected!\n";

	strcat(buffer, argv[2]);				// adds first argument to buffer (required for program)

	for(int i = 3; i < argc; i++)				// adds any additional arguments
	{
		append(buffer,' ');
		strcat(buffer, argv[i]);
	}

	append(buffer, '\n');					// appends newline to finalize message
	cout << "BUFFER: " << buffer;

	send(socketNO, buffer, 64, 0);				// send message

	cout << "MESSAGE!\n";
	n = 1;
	while(n != 0){						// recieve and display 256 bytes at a time, until eof
		n = read(socketNO, in, 256);
		for(int i=0; i<n; i++) {
			cout << in[i];}
	}
	done = close(socketNO);					// close socket connection
	cout << "\nCLOSING SocketNO = " << socketNO << "\ndone = " << done << "\n";
	return 0;						// kill program
}

void append(char* s, char c)	// adds single char to end of c-string
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
