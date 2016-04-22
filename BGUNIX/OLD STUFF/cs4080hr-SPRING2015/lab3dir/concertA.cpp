//	Addison Snyder	
//	Ryan W Ricker
//	Evan Coane

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctime>

using namespace std;

#define NROWS  5
#define NSEATS 8

//function headers
void reserve();
void reserve_seat(int);
void display();
void clear();

/* variables for I/O buffers */
char buffer[256];
char choice[2];
char * cptr;

/* other variables */
int temp = 1234567890;
int seat_id = 0;
char Occupied = 'X', empty[8] = { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' };
int nb, seat, row;
char oneRow[NSEATS], Seats[NROWS][NSEATS];
int fd;

char * prTime()
{
	static char buf[80];
	time_t timeval;
	time(&timeval);
	strncpy(buf, ctime(&timeval), 24);
	return buf;
}

int main() {



	//gets the choice from the user
	char choice = 'a';
	while (choice != 'Q')
	{
		/* Print the menu    */
		printf("\n%s> Welcome to the Concert Hall", prTime());
		printf("\n Menu Choices are: ");
		printf("\n\t Reserve (enter R)");
		printf("\n\t Display (enter D)");
		printf("\n\t Clear   (enter C)");
		printf("\n\t Quit    (enter Q)");
		printf("\n ++++++++++++++++++++++++++++++ \n");
		cout << "Enter a choice: ";
		cin >> choice;

		//figures out which choice the user made and performs the appropriate function
		switch (choice){
		case 'R':	{	reserve();	break;	}
		case 'D':	{	display();	break;	}
		case 'C':	{	clear();	break;	}
		case 'Q':	{	choice = 'Q';	break;	}
		default:	{
				   cout << "Silly Sod! Enter a correct letter!\n";
				   break;			}
		}
	}
	close(fd);
	return 0;
}

void clear(){
	fclose(fopen("concert.dat", "w"));				// create (empty) concert.dat, overwrite pre-existing file
	int file = open("concert.dat", O_WRONLY | O_APPEND);		// reopen it
	write(file, "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO", 40);	// Fill with 40 'Open' chars. Crude, but effective
	return;
}

void reserve(){
	char range[10];
	int r, startSeat, endSeat = 31;

	//gets info from user
	cout << "Please enter row  #:";
	cin >> r;
	cout << "Please enter seat RANGE in '#-#' format group: ";
	cin >> range;
	startSeat = range[0]  - '0';
	if(range[1] == '-'){
		endSeat = (range[2] - '0');
	}
	else
	{
		reserve_seat(range[1]-'0');
		return;
	}

	//make sure the seats are in the proper range
	if(r < 1 || r > 5){
		cout << "The Row Number Is Out Of The Proper Range. \n";
		return;
	}
	if(startSeat < 1 || startSeat > 8){
		cout << "The Starting Seat Number Is Out Of The Proper Range. \n";
		return;
	}
	if(endSeat != 31){
		if(endSeat < 1 || endSeat > 8){
			cout << "The Ending Seat Number Is Out Of The Proper Range. \n";
			return;
		}
	}

	//if a range was entered perform a while loop to reserve several seats

	while(startSeat <= endSeat){
		seat_id = ((r - 1) * 8) + (startSeat - 1);
		reserve_seat(seat_id);
		startSeat++;
	}
	close(fd);
	return;
}

void reserve_seat(int seat_id){

	int r = (seat_id/8)+1;
	int s = (seat_id%8)+1;
	char in[1];

	fd = open("concert.dat", O_RDWR);
	if (fd == -1)
	{
		cout << "Can't Open File!\n";
		exit(1);
	}

	struct flock fl = {F_WRLCK,	SEEK_SET,	0,	0,	0};
	fl.l_start = seat_id;
	fl.l_len = 1;

	while(fcntl(fd, F_SETLKW, &fl) == -1){
		cout << "CAN'T GET A LOCK!\n";
		usleep(1000);
	}
	cout << "LOCKED!\n";
	lseek(fd, seat_id, SEEK_SET);
	nb = read(fd, in, 1);
	cout << "Read byte: " << seat_id << "\n";
	if (in[0] == 'X'){
		time_t currentTime;
		time(&currentTime);
		cout << "Sorry, Row: " << r << " Seat: " << s << " was already reserved." << ctime(&currentTime) << "\n";
		}
	else{
		time_t currentTime;
		time(&currentTime);
		lseek(fd, seat_id, SEEK_SET);
		nb = write(fd, &Occupied, 1);
		cout << "Row: " << r << " Seat: " << s << " Was Successfully Reserved at Time: " << ctime(&currentTime) << "\n";
	}
	fl.l_type = F_UNLCK;
	while(fcntl(fd, F_SETLKW, &fl) == -1){
		cout << "CAN'T GET UNLOCKED!\n";
		usleep(1000);
	}
	cout << "UNLOCKED!\n";
}

void display()
{

	char buffer[40];
	int file = open("concert.dat", O_RDWR);
	nb = pread(file, buffer, 40, 0);

	if (nb == -1)
	{
		cout << "ERROR trying to read from file!";
	}


	for (int i = 0; i < 40; i++){
		if (i % 8 == 0)
			cout << "\n";
		cout << buffer[i];
	}
	cout << "\n";
	return;
}
