///////////////////////////////////////////////////////////////
// FILE NAME: 	main.cpp         
// TITLE:         	Linked List of Classes
// SUBMITTED BY:  	Jacob Boggs
// FOR COURSE:    	CS2020
// DUE DATE:      	045/01/13
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
//
// PURPOSE: 		see README
///////////////////////////////////////////////////////////////
//
// INCLUDED FILES:	
//			snakeGame.h/*.cpp -> listList.h/*.cpp -> listNode.h/*.cpp
//			scoresList.h/*.cpp -> scoresNode.h -> scoresNode.cpp
//				…
///////////////////////////////////////////////////////////////

#include "snakeGame.h"
#include <ctime>

using namespace std;

int main()
{
	snakeGame	*jSnake;	//game object
	listList	*food = new listList,	//food list object
				*bomb = new listList,	//bomb list object
				*snake = new listList,	//snake list object
				*special = new listList,//special food list
				*killer = new listList;	//killer list
	scoresList	*scores = new scoresList;	//scores list object
	scoresNode	*newscore;	//new high score object
	WINDOW		*hwndMain;	//curses window object
	EndEvent	ix;
	int			nrows,		//max screen height
				ncols,		//max screen width
				iresult;	//user input
	string		sresult;	//user input
	bool	loopy = true;	//looping bool
	
	hwndMain = initscr();	//initialize curses for this terminal 

	srand(time(0));				//seed the number generator

	jSnake = new snakeGame(snake,food,bomb,special,killer,scores);	//the game object

	cbreak(); 			// curses call to set terminal to raw mode
	noecho(); 			// curses call to set no echoing
	getmaxyx(hwndMain,nrows,ncols); // curses call to find size of window
	keypad(stdscr,true);	//control keyboard

	jSnake->ncols(ncols);		//set games max x
	jSnake->nrows(nrows);		//set games max y
	nrows = jSnake->nrows()/2 - jSnake->height()/2;
	ncols = jSnake->ncols()/2 - jSnake->width()/2;
	jSnake->x(ncols);			//set game window x pos
	jSnake->y(nrows);			//set game window y pos
	
	jSnake->intro();

	scores->load_records();		//load records
	jSnake->load_settings();	//load settings

	while(loopy)
	{
		cbreak(); 			// curses call to set terminal to raw mode
		noecho(); 			// curses call to set no echoing
		//curs_set(0);
		keypad(stdscr,true);	//control keyboard

		iresult = jSnake->menu();		//show menu screen

		switch(iresult)
		{
		case 1:
			//new game
			ix = jSnake->run();

			//save score
			iresult = jSnake->score();
			if(iresult>0)
			{
				//score is not 0

				newscore = new scoresNode;

				sresult = jSnake->name();
				newscore->name(sresult);	//set name
				
				iresult = jSnake->length();
				newscore->length(iresult);	//set length
				
				iresult = jSnake->score();
				newscore->score(iresult);	//set score
					
				scores->insert(newscore);	//add node to list
				
				//nocbreak();//wait for enter
				//iresult = scores->size();
				//move(0,0);
				//printw("insert - %d",iresult);
				//refresh();
				//move(0,0);
				//addch('0');
				//refresh();
				//getch();

				scores->sort();				//make sure its sorted
				
				/*iresult = scores->size();
				move(0,0);
				printw("sort - %d",iresult);
				refresh();
				getch();*/

				scores->save_records();		//save the high scores
				
				/*iresult = scores->size();
				move(0,0);
				printw("save - %d",iresult);
				refresh();
				getch();*/
			}

			jSnake->endGame(ix);				//notify user
			break;
		case 2:
			//high score
			jSnake->highScores();
			break;
		case 3:
			//settings
			jSnake->settings();
			break;
		case 4:
			//how to
			jSnake->instructions();
			break;
		case 5:
			//quit
			loopy = false;
			break;
		}
	}

	clear();
	sresult = jSnake->name();
	mvprintw(jSnake->nrows()/2-1,jSnake->ncols()/2-7,"Adios, %s!",sresult.c_str());
	refresh();
	endwin();
	return 0;
}


