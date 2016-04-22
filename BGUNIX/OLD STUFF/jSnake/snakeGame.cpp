///////////////////////////////////////////////////////////////
// FILE NAME: 	snakeGame.cpp        
// TITLE:         	snakeGame Implementation File
// PROGRAMMER:	  Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////
#include "snakeGame.h"	//include class definition

//#define KEY_ESC 27		//define esc key

using namespace std;		//use the standard c++ library

///////////////////////////////////////////////////////////////
//	inList			checks to see if a listNode is in a listList
//
//	@param	_check		listNode*	the node to check if in a list
//	@param	_against	listNode*	function will ignore a found node if it is this node
//	@param	_list		listList*	the list to search in
//	…
//	@return bool		true if present
///////////////////////////////////////////////////////////////
bool snakeGame::inList(listNode* _check,listNode* _against,listList* _list) const
{
	listNode	*temp = _list->head();

	while(temp)
	{
		if(*temp==*_check && temp!=_against)	//use overloaded== to check if (x,y)s are equal
			return true;
		temp=temp->n();
	}

	return false;
}

///////////////////////////////////////////////////////////////
//	nextPos		node with (x,y) of "next" node position
//	…
//	@return Point		(x,y) of the next point
///////////////////////////////////////////////////////////////
Point snakeGame::nextPos(listNode* _node) const
{
	Point		nextp;
	int			ir;

	ir = _node->x();
	nextp.x = ir;		//set x-coordinate of _node
	ir = _node->y();
	nextp.y = ir;		//set y-coordinate of _node

	if(Direction=='w')			//(up) y-1
	{
		ir = nextp.y -1;
		nextp.y = ir;
	}
	else if(Direction=='a')		//(left) x-1
	{
		ir = nextp.x -1;
		nextp.x = ir;
	}
	else if(Direction=='s')		//(down) y+1
	{
		ir = nextp.y +1;
		nextp.y = ir;
	}
	else if(Direction=='d')		//(right) x+1
	{
		ir = nextp.x +1;
		nextp.x = ir;
	}
	else
	{
		//no valid nextpPos (not really ever going to happen, just in case...)
		nextp.x = -1;
		nextp.y = -1;
	}

	return nextp;
}

///////////////////////////////////////////////////////////////
//	cls							clears a window and draws a border
//	@param	_hwnd	WINDOW*		the window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::cls(WINDOW*& _hwnd) const
{
	wclear(_hwnd);
	box(_hwnd, ACS_VLINE, ACS_HLINE);	//draw a border around screen
	wrefresh(_hwnd);			//show screen
}

///////////////////////////////////////////////////////////////
//	intro						displays intro screen
//	@param	_hwnd	WINDOW*		the window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::intro(WINDOW*& _hwnd) const
{
	box( _hwnd, ACS_VLINE, ACS_HLINE );	//draw a border around screen
	
	attron(A_BOLD | A_UNDERLINE);		//turn on bold/underline
	//attron(A_UNDERLINE);				//turn on underline
	mvwprintw(_hwnd, nrows()/2-2, ncols()/2 - 12, "jSnake - by Jacob Boggs");
	attroff(A_BOLD | A_UNDERLINE);		//turn off bold/underline
	//attroff(A_UNDERLINE);				//turn off underline
	
	mvwprintw(_hwnd, nrows()/2, ncols()/2 - 11, "CS 2020 Final Project");

	//curs_set(0);			// hide cursor
	move(0,0);		

	refresh();			//show screen

	getch();
	//sleep(5);			//wait
	
	//beep();
	
	cls(_hwnd);			//clear window
}

///////////////////////////////////////////////////////////////
//	menu						displays menu screen
//	@param	_hwnd	WINDOW*		the window
//	…
//	@return int					user selection
///////////////////////////////////////////////////////////////
int snakeGame::menu(WINDOW*& _hwnd) const
{
	//1. New Game
	//2. High Scores
	//3. Settings
	//4. How To Play
	//5. Exit
	//=14 cols 5 rows

	WINDOW		*hwndSub,
				*hwndChild;
	char		sinput[50];
	//char		cresult;
	int			rows=10,//10,
				cols=20;//20;

	cls(_hwnd);		//clear the window
	echo();			//turn echo on
	nocbreak();		//cooked mode (enter)

	hwndSub = newwin(rows,cols,nrows()/2 - rows/2,ncols()/2 - cols/2);//make a new window in _hwnd, centered
	hwndChild = newwin(rows-3,cols-2,nrows()/2 - rows/2+2,ncols()/2 - cols/2+1);//the sub child of new

	box(hwndSub, ACS_VLINE, ACS_HLINE);		//draw a border around screen
	box(hwndChild, ACS_VLINE, ACS_HLINE);

	mvwprintw(hwndSub,1,cols-11,"Main Menu");
	mvwprintw(hwndChild,1,1,"1. New Game");
	mvwprintw(hwndChild,2,1,"2. High Scores");
	mvwprintw(hwndChild,3,1,"3. Settings");
	mvwprintw(hwndChild,4,1,"4. How to Play");
	mvwprintw(hwndChild,5,1,"5. Quit");

	wrefresh(hwndSub);						//show window
	wrefresh(hwndChild);

	wmove(_hwnd,nrows()/2 + rows/2 + 1,ncols()/2 - cols/2 - 7);//move cursor on main screen just below the box
	wprintw(_hwnd,"input: ");

	getstr(sinput);		//wait for enter
	//cresult=wgetch(_hwnd);
	//beep();
	
	delwin(hwndChild);
	delwin(hwndSub);	//destroy window in memory
	cls(_hwnd);			//reset display
	//noecho();			//turn echo off
	//cbreak();			//raw mode (no enter)

	return atoi(sinput);
	//return cresult;
}

///////////////////////////////////////////////////////////////
//	run						starts the game engine
//	…
//	@return int				returns exit code of game
///////////////////////////////////////////////////////////////
EndEvent snakeGame::run()
{
	listNode	*temp,
				*nextNode;
	EndEvent	ix=NO_COL,ix2=NO_COL;
	int			ir=0,ir2=0;
	char	cresult[5];
	WINDOW	*hwndParent,
			*hwndGame;

	setName();					//get/set user's name
	hwndParent = gameParent();	//this is the gameplay window's "border" window
	hwndGame = gameHwnd();		//create gameplay window

	init();						//initialize game values and draw snake
	borders(hwndGame,X,Y);		//draw borders to window
	drawList(Snake,hwndGame);	//draw snake

	nodelay(stdscr,true);		//turn delay off
	
	ix = moveSnake(hwndGame);	//seed the loop
	while(ix < SNAKE_COL)
	{
		ix = moveSnake(hwndGame);	//move the snake
		


		//move all the killers in the Killer list
		ir = Killer->size();	//get number of Killers
		temp = Killer->head();	//start at begininng of list

		for(int j=0;j<ir;j++)
		{
			nextNode = temp->n();	//store next node in list
			ir2 = randInt(1,5);		//get randomn number 1-5
			if(ir2==1)
				ix2 = moveKiller(temp,hwndGame);//move this killer (20% chance of moving) (1/5)
			
			if(ix2==SNAKE_COL)
				ix = KILLER_COL;	//killer got you! exit loop
			
			temp = nextNode;		//examine next node
		}

		move(0,0);
		
		//printw("Speed is: %d",Delay);
		
		wrefresh(hwndGame);
		refresh();

		if(Direction=='w' || Direction=='s')
			usleep((int)(Delay*2.05*1000));	//travel slower on vertical axis to make up for size difference
											//(terminal characters are taller than they are wide)
		else
			usleep(Delay*1000);				//delay (nanoseconds/1 sec = 1 billion)
	}

	nodelay(stdscr,false);	//turn delay on

	wmove(hwndGame,0,Width/2 - 21/2);
	wprintw(hwndGame,"Press enter to continue");
	move(0,0);
	wrefresh(hwndGame);
	refresh();

	getstr(cresult);
	//getch();

	delwin(hwndGame);
	delwin(hwndParent);
	cls();

	return ix;
}

///////////////////////////////////////////////////////////////
//	instructions		displays instructions
//	@param	_hwnd	WINDOW*&	this will be the parent window of instruction window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::instructions(WINDOW*& _hwnd)const
{
	gameWindow	w;
	string		sresult;
	char		cresult[5];
	int			ix,
				iy,
				ih,
				iw;

	cls();		//clear screen
	noecho();	//no echo
	nocbreak();	//cooked mode/wait enter

	ih = 21;	//height
	iw = 46;	//width

	ix = Width/2 - iw/2;	//centered x pos
	iy = Height/2 - ih/2;	//centered y pos

	w = makeWin("jSnake - Instructions",ih,iw,ix,iy);	//create new jSnake window

	ix = 1;
	iy = 1;	//set starting print x and y

	//sresult = "I will use this to display lines of text....";
	//just output this with wprintw...

	sresult = "How to play...";
	wmove(w.hwndChild,iy,ix);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy+=2;	//move down two rows

//	          "***********************************"
	sresult = "This is my take on the classic";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "game Snake.  You must navigate";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "your jSnake across the screen and";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "eat all the FOOD you can.  Be";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());
//	          "***********************************"
	iy++;	//next line

	sresult = "sure to avoid BOMBS and KILLERS.";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "There is also SPECIAL FOOD that";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "has various effects: SLOW, SHRINK,";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "and CLEAR ENEMIES.  Your jSnake";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "will travel faster with each";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "FOOD eaten.  Killers are an enemy";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line
//	          "***********************************"

	sresult = "that move in random, sporadic";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line
	sresult = "patterns and will eat anything they";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "touch.";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;
	
	move(0,0);
	wrefresh(w.hwndChild);
	//refresh();

	getstr(cresult);	//wait for user

	//next page
	cls(w.hwndChild);
	iy = 1;

	sresult = "They only die when they hit a";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;

	sresult = "wall.  They also have a tendency";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "to mob once one is released...";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy+=3;	//next 3 line

	sresult = "Controls:";
	wmove(w.hwndChild,iy,ix);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy+=2;	//next 2 line
//	          "***********************************"
	sresult = "W or UP_ARROW";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "MOVE UP";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "A or LEFT_ARROW";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "MOVE LEFT";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "S or DOWN_ARROW";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "MOVE DOWN";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line
	
	sresult = "D or RIGHT_ARROW";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "MOVE RIGHT";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy+=2;	//next 2 line

	sresult = "Q";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "QUIT GAME";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy++;	//next line

	sresult = "P";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "PAUSE GAME";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	iy+=2;	//next line

	sresult = "PERIOD/COMMA";
	wmove(w.hwndChild,iy,ix+4);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "[CHEAT]";
	wmove(w.hwndChild,iy,ix+20);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	sresult = "SPEED+/SPEED-";
	wmove(w.hwndChild,iy,ix+27);
	wprintw(w.hwndChild,"%s",sresult.c_str());

	move(0,0);
	wrefresh(w.hwndChild);

	getstr(cresult);	//wait for enter

	delwin(w.hwndChild);
	delwin(w.hwndParent);	//free memory
	wrefresh(_hwnd);
}

///////////////////////////////////////////////////////////////
//	highScores					show the high scores list
//	@param	_hwnd	WINDOW*&	this will be the parent window of highsCores
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::highScores(WINDOW*& _hwnd) const
{
	gameWindow	hwndScores;
	scoresNode	*temp = Scores->head();		//start at beginning of list
	string		sresult = "\0";
	char		sinput[5];
	int			ix=0,
				iy=0,
				iresult;

	cls();		//clear the screen
	nocbreak();	//cooked mode/wait for enter
	noecho();	//turn off echo

	ix = Width/2 - 23;
	iy = Height/2 - 10;
	hwndScores = makeWin("jSnake - High Score List",20,46,ix,iy);
	move(0,0);
	refresh();

	Scores->sort();			//make sure list is sorted
	temp = Scores->head();	//start at beginning
	ix = 2;
	iy = 2;

	if(temp)
	{
		//the list is not empty

		//while(temp)
		while((iy<14) && temp)
		{
			//10 records max
			//display number i.e. 1.  2.
			//display name
			//display length
			//display score
			if(iy==2)
			{
				//first run through, display Name, Max Length, Score headers
				attron(A_BOLD);		//turn on bold/underline
				attron(A_UNDERLINE);

				wmove(hwndScores.hwndChild,iy,ix);
				wprintw(hwndScores.hwndChild,"#");

				wmove(hwndScores.hwndChild,iy,ix+6);
				wprintw(hwndScores.hwndChild,"Name");

				wmove(hwndScores.hwndChild,iy,ix+22);
				wprintw(hwndScores.hwndChild,"Size");

				wmove(hwndScores.hwndChild,iy,ix+32);
				wprintw(hwndScores.hwndChild,"Score");

				attroff(A_BOLD);	//turn off bold/underline
				attroff(A_UNDERLINE);
				
				iy+=2;
			}

			//rank at x, name at x+6, length at x+22, score at x+32
			wmove(hwndScores.hwndChild,iy,ix);
			wprintw(hwndScores.hwndChild,"%d.",(iy-3));
		
			sresult = temp->name();					//name
			wmove(hwndScores.hwndChild,iy,ix+6);
			wprintw(hwndScores.hwndChild,"%s",sresult.c_str());

			iresult = temp->length();				//length
			wmove(hwndScores.hwndChild,iy,ix+22);
			wprintw(hwndScores.hwndChild,"%d",iresult);
		
			iresult = temp->score();				//score
			wmove(hwndScores.hwndChild,iy,ix+32);
			wprintw(hwndScores.hwndChild,"%d",iresult);

			iy++;

			temp = temp->next();	//examine next node
		}	//next node until fall off list
	}
	else
	{
		//list is empty
		wmove(hwndScores.hwndChild,iy+1,(50-5)/2-20/2);
		wprintw(hwndScores.hwndChild,"[No High Scores Yet]");
	}

	//23 strlen
	//main window 50 wide
	//-4 for borders
	wmove(hwndScores.hwndChild,iy+1,(50-4)/2-23/2);
	wprintw(hwndScores.hwndChild,"Press enter to continue");

	move(0,0);
	wrefresh(hwndScores.hwndChild);
	getstr(sinput);

	delwin(hwndScores.hwndParent);
	delwin(hwndScores.hwndChild);	//free memory
	refresh();						//refresh screen
}


///////////////////////////////////////////////////////////////
//	setName					sets players name
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::setName(WINDOW*& _hwnd)
{
	char	cresult[50];		
	bool	loopy = true;
	gameWindow	_win;

	echo();
	nocbreak();

	cls();
	_win=makeWin("Enter your name",6);

	while(loopy)
	{
		move(_win.y,_win.x);
		getstr(cresult);
		if(strlen(cresult)>0)
			loopy = false;
	}	

	cls();
	
	delwin(_win.hwndParent);	//free memory
	delwin(_win.hwndChild);

	name(cresult);				//set players name
	refresh();

	cbreak();
	noecho();
}

///////////////////////////////////////////////////////////////
//	makeWin					returns (parent) hwnd of a new jSnake style win
//							with its cursor at (1,1) in writable win
//
//	@param _hwnd	WINDOW*	the parent window
//	@param _caption	string	the caption to display
//	@param _rows	int		the height of the window
//	@param _cols	int		the width of the window
//	@param _x		int		the x-coordinate of the window inside the parent
//	@param _y		int		the y-coordinate of the window inside the parent
//	…
//	@return void
///////////////////////////////////////////////////////////////
gameWindow snakeGame::makeWin(string _caption,int _rows,int _cols, int _x,int _y,WINDOW*& _hwnd) const
{
	WINDOW		*hwndSub,
				*hwndChild;

	gameWindow	temp;

	cls(_hwnd);		//clear the window
	echo();			//turn echo on
	nocbreak();		//cooked mode (enter)

	hwndSub = newwin(_rows,_cols,nrows()/2 - _rows/2,ncols()/2 - _cols/2);//make a new window in _hwnd, centered
	hwndChild = newwin(_rows-3,_cols-2,nrows()/2 - _rows/2+2,ncols()/2 - _cols/2+1);//the sub child of new

	box(hwndSub, ACS_VLINE, ACS_HLINE);		//draw a border around screen
	box(hwndChild, ACS_VLINE, ACS_HLINE);

	mvwprintw(hwndSub,1,_cols-_caption.size()-2,_caption.c_str());
	wmove(hwndChild,1,1);

	wrefresh(hwndSub);						//show window
	wrefresh(hwndChild);

	temp.hwndParent = hwndSub;
	temp.hwndChild = hwndChild;
	temp.y = nrows()/2 - _rows/2 + 3;
	temp.x = ncols()/2 - _cols/2 + 2;
	
	//beep();

	return temp;
}

///////////////////////////////////////////////////////////////
//	moveSnake				moves the snake until an end event occurs
//							end event = eat snake, wall, bomb, killer, user quit,
//	@param	_hwnd	WINDOW*	the game window
//	…
//	@return int				returns exit code of game
///////////////////////////////////////////////////////////////
EndEvent snakeGame::moveSnake(WINDOW* &_hwnd)
{
	int			ir,ir2;
	EndEvent	ix;
	listNode	*temp,		//use this for pointing
				*newNode;	//use this for dynamic memory
	Point		nextp;		//(x,y) of next position
	wchar_t		wresult;
	chtype		cresult;
	WINDOW*		w;

	nodelay(stdscr,true);//turn off delay so will not wait for input
	noecho();		//turn off echo
	cbreak();		//raw mode
	move(0,0);

	w = stats();	//draw stats window
	delwin(w);		//free memory

	ir = Food->size();
	if(ir<1)
		feedSnake(_hwnd);		//make sure >= 1 food on board
		
	//get input and set direction
	wresult=getch();
	switch(wresult)
	{
	case 'W':
	case 'w':
	case KEY_UP:
		if(Direction!='s')
		{
			//if going down, cant go up
			Direction = 'w';
		}
		break;

	case 'S':
	case 's':
	case KEY_DOWN:
		if(Direction!='w')
		{
			//if going up, cant go down
			Direction = 's';
		}
		break;

	case 'A':
	case 'a':
	case KEY_LEFT:
		if(Direction!='d')
		{
			//if going right, cant go left
			Direction = 'a';
		}
		break;

	case 'D':
	case 'd':
	case KEY_RIGHT:
		if(Direction!='a')
		{
			//if going left, cant go right
			Direction = 'd';
		}
		break;

	case 'Q':
	case 'q':
	//case KEY_ESC:
		return USER_QUIT;
		break;

	case '.':
		//cheat for speed up
		Delay-=(int)(Delay*.3);
		break;

	case 't':
		//this is my testing section
		releaseKiller(_hwnd);
		break;

	case ',':
		//cheat for slow down
		Delay+=(int)(Delay*.3);
		break;
		
	case 'p':
		//pause

		wmove(_hwnd,0,Width/2-2);
		wprintw(_hwnd,"PAUSE");
		move(0,0);
		wrefresh(_hwnd);
		refresh();

		//loop until p is pressed again, or q for quit
		wresult='\0';
		while(wresult!='p' && wresult!='q')
			wresult=getch();
		
		for(int j=0;j<5;j++)
		{
			wmove(_hwnd,0,Width/2-2 + j);
			waddch(_hwnd,hBorder);
		}
		move(0,0);
		wrefresh(_hwnd);
		refresh();

		if(wresult=='q')
			return USER_QUIT;		//return user quit

		break;
	}
	//we now have valid input from user if any

	temp = Snake->head();		//point to snake's head
	nextp = nextPos(temp);		//get next relative position
	newNode = new listNode(nextp.x,nextp.y);//create a new node with next (x,y)

	wmove(_hwnd,nextp.y,nextp.x);
	cresult = winch(_hwnd);		//get next position's display character (for checking special food)
	waddch(_hwnd,HeadC);		//draw snake head to next position

	//draw body to old head
	printAtNode(temp,BodyC,_hwnd);//draw new body piece

	//check to see if a collision with anything occured
	ix = isCollision(newNode,temp);

	//see if we have a true end event
	if(ix > SPECIAL_COL)
	{
		delete newNode;			//free memory
		return ix;				//exit function
	}

	//see what we ate...
	switch((int)(ix))
	{
	case NO_COL:
		//ate nothing, just move

		temp = Snake->tail();		//get tail point
		
		printAtNode(temp,' ',_hwnd);//erase tail character

		Snake->pop_back();
		delete newNode;				//delete the new memory reserved

		temp = Snake->tail();

		printAtNode(temp,TailC,_hwnd);//draw new tail character
		break;

	case FOOD_COL:
		//ate normal food
		
		//delete from food list
		//head is already drawn over this position
		//	so dont need to draw ' ' or anything
		Score+=100;					//get 100pts for food
		Delay-= (int)(Delay*.1);	//speed up 10% for each food
		Food->delete_node(newNode);	//delete the eaten food from the Food list AND memory (snake head already wrote over character)
		
		//handle points here************************************
		if(Score%600==0)
			feedSnake(_hwnd);						//feed extra piece of food
		if(Score%1000==0)
			specialSurprise(SLOW_FOOD,_hwnd);		//slow food
		if(Score%1200==0)
			specialSurprise(SHRINK_FOOD,_hwnd);		//shrink food
		if(Score%1500==0)
			specialSurprise(CLEAR_FOOD,_hwnd);		//clear food
		if(Score%300==0)
			plantBomb(_hwnd);						//bombs

		if(Killer->size())
			releaseKiller(_hwnd);					//mob effect of killers
		if(Score%900==0)
			releaseKiller(_hwnd);					//release killers!
		//handle points here************************************

		feedSnake(_hwnd);			//feed snake more food
		break;
	
	case SPECIAL_COL:
		//ate special food
		
		//get what type of food eaten, cresult stored object's display character earlier
		if((int)(cresult)==SlowerC)
		{
			//ate slower food
				
			Delay+= (int)(Delay*.75);		//slow down by 75%
		}
		else if((int)(cresult)==ShrinkC)
		{
			//ate shrink food

			//shrink by 50% while length !=3
			ir2 = Snake->size();		//store snake size

			ir = (int)(ir2*.5);			//get new size
			if(ir<3)(ir=3);				//make sure at least three long (tail,body,head)
			ir=ir2-ir;					//find number of nodes to pop
			for(int j=0;j<ir;j++)
			{
				temp = Snake->tail();		//get tail node
				printAtNode(temp," ",_hwnd);//draw space over tail
				Snake->pop_back();			//pop tail from snake/memory
				temp = Snake->tail();		//get tail node
				printAtNode(temp,TailC,_hwnd);//draw tail character
			}

		}
		else if((int)(cresult)==ClearBadC)
		{
			//ate clear all food
			
			//remove all bombs and killers
			//-draw spaces over characters
			//-delete lists
			
			//bomb list
			temp = Bomb->head();	//start at beginning of bomb list
			while(temp)
			{
				printAtNode(temp,' ',_hwnd);
				temp=temp->n();
			}

			//killer list
			temp = Killer->head();	//start at beginning of killer list
			while(temp)
			{
				printAtNode(temp,' ',_hwnd);
				temp=temp->n();
			}

			//delete both the lists from memory
			Bomb->delete_list();
			Killer->delete_list();

		}

		//done handling special food effects
		//finish special eating move
		Special->delete_node(newNode);//remove from special list

		temp = Snake->tail();		//get tail point			
		printAtNode(temp,' ',_hwnd);//erase tail character
		Snake->pop_back();			//remove tail from memory
		temp = Snake->tail();		//get tail point
		printAtNode(temp,TailC,_hwnd);//draw new tail character
		

		break;
	}

	//now food/specials handled and tail popped if neither happened
	//now must add snake head node with (x,y) of next

	newNode = new listNode(nextp.x,nextp.y);
	Snake->push_front(newNode);		//add node to snake list
	
	ir = Snake->size();				//get new snake size
	if(ir>Length)
		Length = ir;				//update player's max length achieved

	return ix;		//return exit code (will be 0, 1, or 2 here,everything else returned asap)
}

///////////////////////////////////////////////////////////////
//	isCollision		checks to see if a point is in one of the lists
//		
//	@param	_node		listNode*	check this node
//	@param	_against	listNode*	if it is this node, ignore it
//	…
//	@return EndEvent
//		NO_COL			SNAKE_COL		BORDER_COL
//		FOOD_COL		BOMB_COL		USER_QUIT
//		SPECIAL_COL		KILLER_COL
///////////////////////////////////////////////////////////////
EndEvent snakeGame::isCollision(listNode* _node,listNode* _against) const
{	
	Point	p;

	p.x = _node->x();
	p.y = _node->y();

	//food list
	if(inList(_node,_against,Food))
		return FOOD_COL;

	//special list
	if(inList(_node,_against,Special))
		return SPECIAL_COL;

	//snake list
	if(inList(_node,_against,Snake))
		return SNAKE_COL;
	
	//bomb list
	if(inList(_node,_against,Bomb))
		return BOMB_COL;

	//killer list
	if(inList(_node,_against,Killer))
		return KILLER_COL;
	
	//border
	if((p.x==0)||(p.y==0)||(p.x==(Width-1))||(p.y==(Height-1)))
		return BORDER_COL;
	

	return NO_COL;	//has not collided with anything if made it here
}

///////////////////////////////////////////////////////////////
//	borders					draw borders with game settings
//	
//	@param	_hwnd	WINDOW*	the game window
//	@param	_x		int		starting x-coordinate
//	@param	_y		int		starting y-coordinate
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::borders(WINDOW*& _hwnd,int _x, int _y) const
{
	//cls();			//clear screen
	cls(_hwnd);
	noecho();		//turn off echo
	cbreak();		//raw mode

	//draw columns
	for(int j=0;j<Height;j++)
	{
		wmove(_hwnd,j,0);
		waddch(_hwnd,vBorder);
		wmove(_hwnd,j,Width-1);
		waddch(_hwnd,vBorder);
	}

	//draw rows
	for(int j=0;j<Width;j++)
	{
		wmove(_hwnd,0,j);
		waddch(_hwnd,hBorder);
		wmove(_hwnd,Height-1,j);
		waddch(_hwnd,hBorder);
	}

	//draw corners
	wmove(_hwnd,0,0);
	waddch(_hwnd,tlBorder);

	wmove(_hwnd,0,Width-1);
	waddch(_hwnd,trBorder);

	wmove(_hwnd,Height-1,0);
	waddch(_hwnd,blBorder);

	wmove(_hwnd,Height-1,Width-1);
	waddch(_hwnd,brBorder);

	move(0,0);

	wrefresh(_hwnd);
	refresh();
}
///////////////////////////////////////////////////////////////
//	stats						draws the stats window during gameplay
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return WINDOW*				be sure to delwin in calling function
///////////////////////////////////////////////////////////////
WINDOW* snakeGame::stats(WINDOW*& _hwnd) const
{
	WINDOW*		w;
	scoresNode	*temp;
	int			iresult,
				it,
				iy,ix,
				ih,iw;
	string		sresult;

	it = 11;		//my tab length
	ih = STATS_H;	//box height
	iw = STATS_W;	//box width
	ix = STATS_X;
	iy = STATS_Y;	//start pos

	w = newwin(ih,iw,iy,ix);	//create new window

	cls(w);		//draw boarder around window

	ix = 2;
	iy = 1;	//start pos

	sresult = Name;
	wmove(w,iy,ix);
	wprintw(w,"Name:");
	wmove(w,iy,ix+it-5);
	wprintw(w,"%s",sresult.c_str());
	
	iy++;

	iresult = Score;
	wmove(w,iy,ix);
	wprintw(w,"Score:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy++;

	temp = Scores->head();
	if(temp)
		iresult = temp->score();
	else
		iresult = 0;
	if(Score>iresult)(iresult=Score);
	wmove(w,iy,ix);
	wprintw(w,"Top Score:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy+=2;

	wmove(w,iy,ix);
	wprintw(w,"Activity");

	iy++;

	it+=2;	//tab out the values a few additional spaces since they are all 1 char

	iresult = Snake->size();
	wmove(w,iy,ix);
	wprintw(w,"Length:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy++;

	iresult = Food->size();
	wmove(w,iy,ix);
	wprintw(w,"Food:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy++;

	iresult = Special->size();
	wmove(w,iy,ix);
	wprintw(w,"Special:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy++;

	iresult = Bomb->size();
	wmove(w,iy,ix);
	wprintw(w,"Bombs:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy++;

	iresult = Killer->size();
	wmove(w,iy,ix);
	wprintw(w,"Killers:");
	wmove(w,iy,ix+it);
	wprintw(w,"%d",iresult);

	iy+=2;

	wmove(w,iy,ix);
	wprintw(w,"Legend");

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Food:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",FoodC);

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Bomb:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",BombC);

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Killer:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",KillerC);

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Shrink:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",ShrinkC);

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Slow:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",SlowerC);

	iy++;

	wmove(w,iy,ix);
	wprintw(w,"Clear:");
	wmove(w,iy,ix+it);
	wprintw(w,"%c",ClearBadC);

	iy++;

	move(0,0);
	wrefresh(w);
	refresh();

	return w;
}

///////////////////////////////////////////////////////////////
//	drawList					draws a listList in a WINDOW
//	@param	_list	listList	the list
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return int					returns exit code of game
///////////////////////////////////////////////////////////////
void snakeGame::drawList(listList*& _list,WINDOW*& _hwnd) const
{
	listNode	*temp=_list->head();		//start at head of list

	//traverse list and output c at node's (x,y)
	while(temp)
	{
		wmove(_hwnd,temp->y(),temp->x());
		waddch(_hwnd,temp->c());
		temp=temp->n();
	}

	move(0,0);
	wrefresh(_hwnd);

}

///////////////////////////////////////////////////////////////
//	feedSnake					feed the snake some food
//
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::feedSnake(WINDOW*& _hwnd)
{
	int		rx=0,
			ry=0;
	bool	loopy=true;
	listNode*temp = new listNode(0,0,FoodC);

	while(loopy)
	{
		rx=randInt(1,Width-2);
		ry=randInt(1,Height-2);
		temp->x(rx);
		temp->y(ry);
		if(!inList(temp,0,Food) && !inList(temp,0,Snake) && !inList(temp,0,Bomb) && !inList(temp,0,Special) && !inList(temp,0,Killer))
			loopy=false;
	}

	Food->push_front(temp);
	wmove(_hwnd,ry,rx);
	waddch(_hwnd,temp->c());
	wrefresh(_hwnd);
	//refresh();
}

///////////////////////////////////////////////////////////////
//	plantBomb					plant a bomb on the board
//
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::plantBomb(WINDOW*& _hwnd)
{
	int		rx=0,
			ry=0;
	bool	loopy=true;
	listNode*temp = new listNode(0,0,BombC);

	while(loopy)
	{
		rx=randInt(1,Width-2);
		ry=randInt(1,Height-2);
		temp->x(rx);
		temp->y(ry);
		if(!inList(temp,0,Food) && !inList(temp,0,Snake) && !inList(temp,0,Bomb) && !inList(temp,0,Special) && !inList(temp,0,Killer))
			loopy=false;
	}

	Bomb->push_front(temp);
	wmove(_hwnd,ry,rx);
	waddch(_hwnd,temp->c());
	wrefresh(_hwnd);
	refresh();
}

///////////////////////////////////////////////////////////////
//	releaseKiller				release the killers!
//
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::releaseKiller(WINDOW*& _hwnd)
{
	int		rx=0,
			ry=0;
	bool	loopy=true;
	listNode*temp = new listNode(0,0,KillerC);

	while(loopy)
	{
		rx=randInt(1,Width-2);
		ry=randInt(1,Height-2);
		temp->x(rx);
		temp->y(ry);
		if(!inList(temp,0,Food) && !inList(temp,0,Snake) && !inList(temp,0,Bomb) && !inList(temp,0,Special) && !inList(temp,0,Killer))
			loopy=false;
	}

	Killer->push_front(temp);
	wmove(_hwnd,ry,rx);
	waddch(_hwnd,temp->c());
	wrefresh(_hwnd);
	//refresh();	
}

/////////////////////////////////////////////////////////////////
//	moveKiller					moves the killers
//
//	@param	_node	listNode*	the killer node to move
//	@param	_hwnd	WINDOW*		the game window
//	…
//	@return EndEvent
/////////////////////////////////////////////////////////////////
EndEvent snakeGame::moveKiller(listNode*& _node,WINDOW*& _hwnd)
{
	listNode	*newNode;
	Point		np;
	EndEvent	ix;
	char		oldDir=Direction,
				tempDir=Direction;
	int			ir;

	//get a random direction
	ir = randInt(1,4);		//generate random direction
	switch(ir)				//translate random direction to corresponding char
	{
	case 1:
		tempDir = 'w';		//up
		break;
	case 2:
		tempDir = 's';		//down
		break;
	case 3:
		tempDir = 'a';		//left
		break;
	case 4:
		tempDir = 'd';		//right
		break;
	}

	Direction = tempDir;				//set temporary direction	
	np = nextPos(_node);				//get next relative (y,x) to _node and direction
	printAtNode(_node,' ',_hwnd);		//erase old killer
	//ix = isCollision(newNode,_node);		//check if this node appears in any lists already
	Killer->delete_node(_node);			//remove old killer from list
	newNode = new listNode(np.x,np.y,KillerC);	//allocate new memory
	printAtNode(newNode,KillerC,_hwnd);	//draw new killer
	ix = isCollision(newNode,0);
	Killer->push_front(newNode);		//add new killer to list

	//at this point, screen is updated, _node does not exist, and newNode is in Killer
	
	newNode = new listNode(np.x,np.y);	//use this to remove objects from their lists

	//handle collision
	switch(ix)
	{
	case NO_COL:
		//dont need to do anything here except release memory
		delete newNode;
		break;
	case FOOD_COL:
		//remove the node from the food list
		Food->delete_node(newNode);
		break;
	case SPECIAL_COL:
		//remove the node from the special list
		Special->delete_node(newNode);
		break;
	case SNAKE_COL:
		//the new killer ate you! end game
		delete newNode;					//free memory
		break;
	case BOMB_COL:
		//remove the node from the bomb list
		Bomb->delete_node(newNode);		//free memory
		break;
	case KILLER_COL:
		//remove the node from the killer list (CANNIBAL KILLERS!)
		Killer->delete_node(newNode);	//free memory
		break;
	case BORDER_COL:
		//fix broken wall

		//printAtNode(newNode,np.y,_hwnd);

		if(np.x<0)(np.x=0);
		if(np.y<0)(np.y=0);

		if((np.x==0)||(np.x==(Width-1)))
		{
			wmove(_hwnd,newNode->y(),newNode->x());
			waddch(_hwnd,ACS_VLINE);
			wrefresh(_hwnd);
			//printAtNode(newNode,ACS_HLINE,_hwnd);	//replace horizontal wall piece
		}
		if((np.y==0)||(np.y==(Height-1)))
		{
			wmove(_hwnd,newNode->y(),newNode->x());
			waddch(_hwnd,ACS_HLINE);
			wrefresh(_hwnd);
			//printAtNode(newNode,ACS_VLINE,_hwnd);	//replace vertical wall piece
		}
		Killer->delete_node(newNode);			//free memory
		break;
	case USER_QUIT:
		//wont ever get here, but ya know...
		delete newNode;				//free memory
		break;
	}
	
	Direction = oldDir;		//set the game direction back to where it was
	return ix;				//return the collision code
}


//int snakeGame::moveKiller(WINDOW*& _hwnd)
//{
//	listNode	*killert = Killer->head(),	//start at beginning of killer list
//				*nPos=0,						//next killer position
//				*temp=0,						//pointer to delete
//				*prev=killert;						//pointer to prev node
//	int			iresult=0;
//	char		tempDir=Direction,
//				newDir='\0';
//
//	tempDir = Direction;		//get old direction
//
//	while(killert)
//	{
//		//traverse list and handle each killer
//
//		temp = killert;
//
//		//get random direction
//		iresult = randInt(1,4);
//		switch(iresult)
//		{
//		case 1:
//			//up
//			newDir = 'w';
//			break;
//		case 2:
//			//down
//			newDir = 's';
//			break;
//		case 3:
//			//left
//			newDir = 'a';
//			break;
//		case 4:
//			//right
//			newDir = 'd';
//			break;
//		}
//
//		iresult = 0;				
//		Direction = newDir;			//set new random direction
//		
//		nPos = nextPos(temp);	//get next position according to random direction
//		nPos->c(KillerC);			//set nodes char
//
//		wmove(_hwnd,temp->y(),temp->x());
//		waddch(_hwnd,' ');		//blank out old killer spot
//		wmove(_hwnd,nPos->y(),nPos->x());
//		waddch(_hwnd,nPos->c());//draw new killer spot
//
//		if(inList(nPos,Food))
//		{
//			//in food list
//			Food->delete_node(nPos);	//remove from Food
//		}
//		else
//		if(inList(nPos,Bomb))
//		{
//			//in bomb list
//			Bomb->delete_node(nPos);	//remove from Bomb
//		}
//		else
//		if(inList(nPos,Snake))
//		{
//			//in snake list
//			//if(nPos)
//			//	delete nPos;
//
//			iresult = 44;	//set error code
//		}
//		else
//		if(inList(nPos,Killer))
//		{
//			//in killer list
//			//Killer->delete_node(nPos);	//remove from Killer
//			iresult=1;	//set flag so we dont add this node to list(again)
//		}
//		if(inList(nPos,Special))
//		{
//			//in special list
//			Special->delete_node(nPos);	//remove from Special
//		}
//		else
//		if((nPos->x()==0) || (nPos->x()==Width-1))
//		{
//			//ran into vertical border/just remove this node [DONT ADD BACK INTO KILLER]
//			wmove(_hwnd,nPos->y(),nPos->x());
//			waddch(_hwnd,vBorder);	//fix wall
//			
//			if(*temp==*Killer->head())
//			{
//				//at head of list
//				killert = killert->n();		//move killert to next node
//				Killer->head(killert);		//set new head of Killer
//				delete temp;				//remove old node
//			}
//			else
//			{
//				//not head
//				prev->n(temp->n());		//link prev node to nxt node
//				killert = temp->n();	//move killert to next node
//				delete temp;			//delete old node
//			}
//
//			//if(nPos)
//			//delete nPos;			//make sure we dont have memory floating around...
//			iresult=1;				//set result flag so we dont add it
//		}
//		else
//		if((nPos->y()==0) || (nPos->y()==Height-1))
//		{
//			//ran into horizontal border/just remove this node [DONT ADD BACK INTO KILLER]
//			wmove(_hwnd,nPos->y(),nPos->x());
//			waddch(_hwnd,hBorder);	//fix wall
//			
//			if(*temp==*Killer->head())
//			{
//				//at head of list
//				killert = killert->n();		//move killert to next node
//				Killer->head(killert);		//set neww head of Killer
//				delete temp;				//remove old node
//			}
//			else
//			{
//				//not head
//				prev->n(temp->n());		//link prev node to nxt node
//				killert = temp->n();	//move killert to next node
//				delete temp;			//delete old node
//			}
//
//			//if(nPos)
//			//delete nPos;			//make sure we dont have memory floating around...
//
//			iresult=1;				//set result flag so we dont add it
//		}
//		else
//		{
//			//not in any list, just move
//			//if(nPos)
//			//delete nPos;			//make sure we dont have memory floating around...
//		}
//
//		if(!iresult)
//		{
//			//nothing special happened...
//			//remove old killer,add new killer to Killer
//			nPos = nextPos(temp);		//get next node again because deleted
//			nPos->c(KillerC);			//set nodes char
//
//			if(*killert==*Killer->head())
//			{
//				//at head node
//				nPos->n(temp->n());		//link nPos next point
//				Killer->head(nPos);		//set new head
//				delete temp;			//remove old head
//			}
//			else
//			{
//				//in middle or end of list
//				nPos->n(temp->n());		//set nPos next to next node
//				prev->n(nPos);			//set prev next to nPos
//				killert=nPos;			//set killert to correct node
//				delete temp;			//delete old killer
//			}			
//		}
//	
//		if(killert)
//		{
//			prev = killert;			//set the previous node
//			killert=killert->n();	//examine next node/stop if killert==null (falls off list)
//		}
//
//		move(0,0);
//		wrefresh(_hwnd);
//		refresh();
//
//		if(iresult==4)
//			break;			//exit loop if snake collision
//		else
//			iresult=0;		//reset error code if exiting this iteration
//
//	}//end loop
//
//	Direction = tempDir;	//set game direction back to true value
//	return iresult;
//}

///////////////////////////////////////////////////////////////
//	specialSurprise				release the killers!
//
//	@param	_hwnd	WINDOW*		the game window
//	@param	_spt	SpecialType	the type of special food to give
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::specialSurprise(SpecialType _spt,WINDOW*& _hwnd)
{
	int		rx=0,
			ry=0;
	bool	loopy=true;
	listNode*temp = new listNode;

	switch(_spt)
	{
	case SLOW_FOOD:
		temp->c(SlowerC);
		break;
	case CLEAR_FOOD:
		temp->c(ClearBadC);
		break;
	case SHRINK_FOOD:
		temp->c(ShrinkC);
		break;
	}

	//get valid random (x,y)
	while(loopy)
	{
		rx=randInt(1,Width-2);
		ry=randInt(1,Height-2);
		temp->x(rx);
		temp->y(ry);
		if(!inList(temp,0,Food) && !inList(temp,0,Snake) && !inList(temp,0,Bomb) && !inList(temp,0,Special) && !inList(temp,0,Killer))
			loopy=false;
	}

	//add the special node to the list and draw on screen
	Special->push_front(temp);
	wmove(_hwnd,ry,rx);
	waddch(_hwnd,temp->c());
	wrefresh(_hwnd);
	refresh();	
}

///////////////////////////////////////////////////////////////
//	randInt					returns a randomn number within bounds
//	@param	_lower	int		lower bound
//	@param	_upper	int		upper bound
//	…
//	@return int	
///////////////////////////////////////////////////////////////
int snakeGame::randInt(int _lower,int _upper) const
{
	int temp;
	
	temp = rand() % (_upper - _lower + 1) + _lower;

	return temp;
}

///////////////////////////////////////////////////////////////
//	gameParent					returns parent window to gameplay screen
//								(make hwndGame in this window, not stdscr)
//	…
//	@return WINDOW*				the proper hwndGame parent window
///////////////////////////////////////////////////////////////
WINDOW* snakeGame::gameParent() const
{
	WINDOW*		temp;
	int			nH,	//new window's height
				nW,	//new window's width
				nX,	//new window's x
				nY;	//new window's y

	nH = NRows - 2;
	nW = NCols - STATS_X - STATS_W-1;
	nX = STATS_X + STATS_W;
	nY = STATS_Y;

	temp = newwin(nH,nW,nY,nX);

	cls(temp);	//draw borders

	return temp;
}

///////////////////////////////////////////////////////////////
//	gameHwnd					returns window to gameplay screen
//								(make hwndGame in this gamneParent)
//	…
//	@return WINDOW*				the proper hwndGame window
///////////////////////////////////////////////////////////////
WINDOW* snakeGame::gameHwnd()
{
	WINDOW*		temp;

	int			nH,
				nW,
				iY,
				iX;
	
	nH = NRows - 2;					//parents height
	nW = NCols - STATS_X - STATS_W -1;	//parents width
	
	//make sure height and width dont exceed the max
	if(Height > (nH-2))
		Height = nH-2;
	if(Width > (nW-2))
		Width = nW-2;
	//...not too small
	if(Height < 5)
		Height = 5;
	if(Width < 5)
		Width = 5;

	iY = nH/2 - Height/2 + STATS_Y;				//centered Y
	iX = nW/2 - Width/2 + STATS_X + STATS_W;	//centered X

	Y = iY;
	X = iX;		//set games starting (y,x)

	temp = newwin(Height,Width,Y,X);

	cls(temp);		//draw borders

	return temp;
}

///////////////////////////////////////////////////////////////
//	printAtNode			print strin at node's (x,y)
//
//	@param	_hwnd	WINDOW*&	the game window
//	@param	_print	string		the string to print
//	@param	_node	listNode	the node to use
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::printAtNode(listNode* _node,string _print,WINDOW* &_hwnd) const
{
	wmove(_hwnd,_node->y(),_node->x());
	wprintw(_hwnd,_print.c_str());

	move(0,0);
	wrefresh(_hwnd);
	refresh();

}

///////////////////////////////////////////////////////////////
//	printAtNode				print char at _node (x,y)
//
//	@param	_hwnd	WINDOW*&	the game window
//	@param	_print	char		the char to print
//	@param	_node	listNode	the node to use
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::printAtNode(listNode* _node,char _print,WINDOW* &_hwnd) const
{
	wmove(_hwnd,_node->y(),_node->x());
	waddch(_hwnd,_print);

	move(0,0);
	wrefresh(_hwnd);
	refresh();

}

///////////////////////////////////////////////////////////////
//	endGame					notify game end
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::endGame(EndEvent _ix,WINDOW*& _hwnd)
{
	gameWindow	w;

	int	ix,iy,
		iw,ih,
		ir;
	string sr="\0";

	w.hwndChild=0;
	w.hwndParent=0;

	cls();

	ih = 10;
	iw = 43;
	ix = NCols/2-iw/2;
	iy = NRows/2-ih/2;

	switch(_ix)
	{
	case SNAKE_COL:
		w=makeWin("You ate yourself",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"You know what you doing?!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,2);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,2);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	case BOMB_COL:
		w=makeWin("You ate a bomb",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"Someone set us up the bomb!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,2);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,2);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	case KILLER_COL:
		w=makeWin("A killer got you!",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"All your base are belong to killers!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,2);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,2);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	case BORDER_COL:
		w=makeWin("You hit a wall",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"You are on the way to destruction!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,2);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,2);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	case USER_QUIT:
		w=makeWin("Quitter",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"Make your time!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,2);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,2);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	default:
		w=makeWin("Why are you here",ih,iw,ix,iy);
		wmove(w.hwndChild,1,2);
		wprintw(w.hwndChild,"You discovered the MATRIX!");
		wmove(w.hwndChild,3,2);
		ir=Score;
		wprintw(w.hwndChild,"Score: %d",ir);
		wmove(w.hwndChild,4,1);
		ir=Length;
		wprintw(w.hwndChild,"Max Length: %d",ir);
		wmove(w.hwndChild,5,1);
		ir=allTimeRank(Name,Score);
		wprintw(w.hwndChild,"All Time Rank: %d",ir);
		break;
	}

	move(0,0);
	wrefresh(w.hwndChild);
	refresh();
	
	getch();

	delwin(w.hwndChild);
	delwin(w.hwndParent);
}

///////////////////////////////////////////////////////////////
//	allTimeRank			gives player all time scores ranking
//	…
//	@return int
///////////////////////////////////////////////////////////////
int snakeGame::allTimeRank(string _name, int _score)
{
	scoresNode	*traverse = Scores->head();	//start at beginning of list;
	int			ir,count=0;
	string		sr;

	Scores->sort();						//make sure list is sorted
	while(traverse)
	{
		count++;						//update count
		ir = traverse->score();			//get current nodes score
		sr = traverse->name();			//get current nodes name

		if((ir==_score)&&(sr==_name))
			return count;				//return counting number

		traverse=traverse->next();		//examine next node
	}

	return 0;
}

///////////////////////////////////////////////////////////////
//	settings					get/set settings
//
//	@param	_hwnd	WINDOW*&	this is the parent window of the settings window (stdscr)
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::settings(WINDOW*& _hwnd)
{
	gameWindow	w;
	int			ix,iy,
				ih,iw,
				ir;
	char		cr='\0';
	char		sr[50];

	w.hwndChild=0;
	w.hwndParent=0;	//initialize windows
	
	curs_set(0);

	cbreak();
	echo();

	//loop until quit
	while(*sr!='q')
	{
		ih = 21;
		iw = 28;
		ix = NCols/2 - iw/2;
		iy = NRows/2 - ih/2;
		w = makeWin("jSnake - Settings",ih,iw,ix,iy);

		ix = 2;
		iy = 1;

		//display selection numbers
		for(int j=1; j<12;j++)
		{
			wmove(w.hwndChild,iy+j-1,ix);
			wprintw(w.hwndChild,"%d.",j);
		}

		//display captions/values
		ix = 6;
		iy = 1;

		cr = FoodC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Food:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = HeadC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Head:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = BodyC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Body:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = TailC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Tail:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = BombC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Bomb:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = SlowerC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Slower:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = ClearBadC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Clear Bad:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = KillerC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Killer:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		cr = ShrinkC;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Shrink:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%c",cr);
		iy++;

		ir = Height;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Height:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%d",ir);
		iy++;

		ir = Width;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Width:");
		wmove(w.hwndChild,iy,ix + 15);
		wprintw(w.hwndChild,"%d",ir);
		iy+=2;

		ix = 2;
		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"D for defaults");
		iy++;

		wmove(w.hwndChild,iy,ix);
		wprintw(w.hwndChild,"Q for quit");
		iy++;

		move(NRows/2 + ih/2 -2,NCols/2 - iw/2+3);//move cursor on main screen just below last option
	
		wrefresh(w.hwndChild);
		wrefresh(w.hwndChild);
		refresh();

		//cr = getch();
		getstr(sr);

		if(strcmp(sr,"d")==0)
		{
			//set defaults
			FoodC = (char)(211);//Ó
			HeadC = (char)(214);//Ö
			BodyC = (char)(244);//ô
			TailC = (char)(215);//×
			BombC = (char)(216);//Ø
			SlowerC = (char)(247);//÷
			ClearBadC = (char)(167);//§
			KillerC	= (char)(199);//Ç
			ShrinkC = (char)(171);//«
			Height = 20;
			Width = 40;
		}
		else
		{
			ir=atoi(sr)-1;
			//check for valid input ()
			switch(ir)
			{
			case FOODC:
			case HEADC:
			case BODYC:
			case TAILC:
			case BOMBC:
			case SLOWERPC:
			case CLEARBADC:
			case KILLERC:
			case SHRINKC:
			case HEIGHT:
			case WIDTH:
				setAttr((SettingSelect)(ir));
	
			default:
				break;
			}
		}

		delwin(w.hwndChild);
		delwin(w.hwndParent);
	}	//end main loop
	
	save_settings();
	refresh();
}

///////////////////////////////////////////////////////////////
//	setAttr						get/set new attr
//
//	@param	_index	int			the character index
//	@param	_hwnd	WINDOW*&	this is the parent window of the settings window (stdscr)
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::setAttr(SettingSelect _index,WINDOW*& _hwnd)
{
	gameWindow	w;
	int		ih,ix,
			iy,iw,ir=0;
	char	sr[51]="";
	curs_set(0);
	ih=11;				//height	
	iw=23;				//width
	ix=NCols/2 - iw/2;	//x-coordinate relative to stdscr
	iy=NRows/2 - ih/2;	//y-coordinate relative to stdscr
	w = makeWin("Change Setting",ih,iw,ix,iy);//window with our setting
	wrefresh(_hwnd);
	refresh();

	ix = NCols/2 - iw/2+2;
	iy = NRows/2 - ih/2+3;

	move(iy,ix);

	//	FoodC = (char)(211);//Ó
	//	HeadC = (char)(214);//Ö
	//	BodyC = (char)(244);//ô
	//	TailC = (char)(215);//×
	//	BombC = (char)(216);//Ø
	//	SlowerC = (char)(247);//÷
	//	ClearBadC = (char)(167);//§
	//	KillerC	= (char)(199);//Ç
	//	ShrinkC = (char)(171);//«
	//	Height = _height;
	//	Width = _width;
	switch(_index)
	{
	case FOODC:
		printw("Current Food: %c",FoodC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Food:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			FoodC=(char)(211);
		else
			FoodC = *sr;

		break;

	case HEADC:
		printw("Current Head: %c",HeadC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Head:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			HeadC=(char)(214);
		else
			HeadC = *sr;

		break;

	case BODYC:
		printw("Current Body: %c",BodyC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Body:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			BodyC=(char)(244);
		else
			BodyC = *sr;

		break;

	case TAILC:
		printw("Current Tail: %c",TailC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Tail:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			TailC=(char)(215);
		else
			TailC = *sr;

		break;

	case BOMBC:
		printw("Current Bomb: %c",BombC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Bomb:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			BombC=(char)(216);
		else
			BombC = *sr;

		break;

	case SLOWERPC:
		printw("Current Slower: %c",SlowerC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Slower:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			SlowerC=(char)(247);
		else
			SlowerC = *sr;

		break;

	case CLEARBADC:
		printw("Current Clear: %c",ClearBadC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Clear:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			ClearBadC=(char)(167);
		else
			ClearBadC = *sr;

		break;

	case KILLERC:printw("Current Killer: %c",KillerC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Killer:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			KillerC=(char)(199);
		else
			KillerC = *sr;

		break;

	case SHRINKC:
		printw("Current Shrink: %c",ShrinkC);
		iy+=2;
		move(iy,ix);
		printw("Enter new Shrink:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			ShrinkC=(char)(171);
		else
			ShrinkC = *sr;

		break;

	case HEIGHT:
		printw("Current Height: %d",Height);
		iy+=2;
		move(iy,ix);
		printw("Enter new Height:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			Height=21;
		else
		{
			ir=atoi(sr);
			if(ir)
				Height = ir;
		}

		break;

	case WIDTH:
		printw("Current Width: %d",Width);
		iy+=2;
		move(iy,ix);
		printw("Enter new Width:");
		iy+=3;
		move(iy,ix);
		printw("[\"def\" for default]");
		iy-=2;

		while(*sr=='\0')
		{
			move(iy,ix);
			getstr(sr);
		}

		if(strcmp(sr,"def")==0)
			Width = 41;
		else
		{
			ir=atoi(sr);
			if(ir)
				Width = ir;
		}

		break;

	default:
		break;
	}

	wrefresh(w.hwndChild);

	//getstr(sr);
	//cr = getch();
	//getstr(sr);

	delwin(w.hwndChild);
	delwin(w.hwndParent);
	cls();
}

///////////////////////////////////////////////////////////////
//	load_settings		loads settings [jsnake.jss]
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::load_settings(string _path)
{
	fstream		file;
	string		sb="\0";
	int			ib=0;
	char		cb='\0';
	SettingSelect	ss=FOODC;

	file.open(_path.c_str(),ios::in);	//try to open file
	getline(file,sb);					//try to read file

	while(file.good())
	{
		//the file still has data to load

		if(sb!="\0")
		{
			switch(ss)
			{
			case FOODC:
				cb=sb[0];
				FoodC = cb;
				break;
			case HEADC:
				cb=sb[0];
				HeadC = cb;
				break;
			case BODYC:
				cb=sb[0];
				BodyC = cb;
				break;
			case TAILC:
				cb=sb[0];
				TailC = cb;
				break;
			case BOMBC:
				cb=sb[0];
				BombC = cb;
				break;
			case SLOWERPC:
				cb=sb[0];
				SlowerC = cb;
				break;
			case CLEARBADC:
				cb=sb[0];
				ClearBadC = cb;
				break;
			case KILLERC:
				cb=sb[0];
				KillerC = cb;
				break;
			case SHRINKC:
				cb=sb[0];
				ShrinkC = cb;
				break;
			case HEIGHT:
				ib=atoi(sb.c_str());
				Height = ib;
				break;
			case WIDTH:
				ib=atoi(sb.c_str());
				Width = ib;
				break;
			default:
				break;
			}

			ss = (SettingSelect)(ss+1);	//go to next setting index to load
		}

		getline(file,sb);			//attempt to read in value
	}
	file.close();					//close the file
}

///////////////////////////////////////////////////////////////
//	save_settings		saves settings [jsnake.jss]
//	…
//	@return void
///////////////////////////////////////////////////////////////
void snakeGame::save_settings(string _path)
{
	fstream file;

	file.open(_path.c_str(),ios::out);

	file << FoodC << endl;
	file << HeadC << endl;
	file << BodyC << endl;
	file << TailC << endl;
	file << BombC << endl;
	file << SlowerC << endl;
	file << ClearBadC << endl;
	file << KillerC << endl;
	file << ShrinkC << endl;
	file << Height << endl;
	file << Width << endl;

	file.close();
}







