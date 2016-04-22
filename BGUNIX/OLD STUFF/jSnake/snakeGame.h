///////////////////////////////////////////////////////////////
// FILE NAME: 	snakeGame.h         
// TITLE:         	snakeGame Header File
// PROGRAMMER:  	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#ifndef SNAKEGAME_H
#define SNAKEGAME_H		//include guard

#define STATS_H 20
#define STATS_W 20
#define STATS_X 2
#define STATS_Y 1		//dimensions of stats window during gameplay

#include "listList.h"	//listList library
#include "scoresList.h"	//scoresList library
#include <string>		//include string library
#include <curses.h>		//curses library

using namespace std;

enum SpecialType{SLOW_FOOD,CLEAR_FOOD,SHRINK_FOOD};//special food types
enum EndEvent{NO_COL,FOOD_COL,SPECIAL_COL,SNAKE_COL,BOMB_COL,KILLER_COL,BORDER_COL,USER_QUIT};//collision events
enum SettingSelect{FOODC,HEADC,BODYC,TAILC,BOMBC,SLOWERPC,CLEARBADC,KILLERC,SHRINKC,HEIGHT,WIDTH};

struct gameWindow
{
	WINDOW	*hwndParent,
			*hwndChild;
	int		x,		//cursor main windows x-y-coordinates
			y;		//for child window position
};

struct Point
{
	int x,			//x-coordinate
		y;			//y-coordinate
};

class snakeGame
{
	private:

		int		Collision,		//collision index: 0=none, 1=food, 2=snake, 3=bomb, 4=border
				Score,			//score
				Length,			//max length of snake during game
				Delay,			//time to wait to redraw screen
				NRows,			//maximum window rows (y)
				NCols,			//maximum window cols (x)
				Height,			//height of game window
				Width,			//width of game window
				X,				//the game screen x value
				Y,				//the game screen y value
				Step;			//this holds the "game step" number. 1 step is one move
	
		wchar_t	vBorder,		//the game's vertical border	
				hBorder,		//the game's horizontal border
				tlBorder,		//top left corner
				trBorder,		//top right corner
				blBorder,		//bottom left border
				brBorder;		//bottom right border		

		char	Direction,		//current direction (w,a,s,d,) (up, left, down, right respectively)
				FoodC,			//food character
				BodyC,
				HeadC,
				TailC,
				BombC,
				KillerC,
								//*=special food
				SlowerC,		//*reduces delay by 50%
				ClearBadC,		//*removes killers and bombs
				ShrinkC;		//*shrinks snake

		string	Name;		//players name

		scoresList	*Scores;	//high score list

		listList	*Snake,		//the game's snake list
					*Food,		//the game's food list
					*Bomb,		//the game's bomb list
					*Special,	//the game's special food list
					*Killer;	//the game's killer list
	public:

		//constructor
		snakeGame(listList* &_snake,listList* &_food,listList* &_bomb,listList* &_special,listList* &_killer,scoresList*& _scores,int _height=21, int _width=41,int _x=5,int _y=5,int _maxX=50,int _maxY=30)
		{
			Collision = 0;
			Score = 0;
			Delay = 300;
			Length=0;
			vBorder = ACS_VLINE;
			hBorder = ACS_HLINE;
			tlBorder = ACS_ULCORNER;
			trBorder = ACS_URCORNER;
			blBorder = ACS_LLCORNER;
			brBorder = ACS_LRCORNER;
			Direction = 'd';
			FoodC = (char)(211);//Ó
			HeadC = (char)(214);//Ö
			BodyC = (char)(244);//ô
			TailC = (char)(215);//×
			BombC = (char)(216);//Ø
			SlowerC = (char)(247);//÷
			ClearBadC = (char)(167);//§
			KillerC	= (char)(199);//Ç
			ShrinkC = (char)(171);//«
			Step = 0;
			NRows = _maxY;
			NCols = _maxX;
			Name = "s1Lky sL1m";
			Height = _height;
			Width = _width;
			X=_x;
			Y=_y;
			Scores = _scores;	//required
			Snake = _snake;		//required
			Food = _food;		//required
			Bomb = _bomb;		//required
			Special = _special;	//required
			Killer = _killer;	//required
		}

		//destructor
		~snakeGame()
		{
			Snake->delete_list();
			Food->delete_list();
			Bomb->delete_list();
			Killer->delete_list();
			Special->delete_list();
			Scores->delete_list();

		}

		//class functions
		
		void	borders(WINDOW*& _hwnd=stdscr,int _x=1,int _y=1) const;	//draws the game screen border according to settings
		void	drawList(listList*&,WINDOW*&) const;	//draws a lists contents according to (x,y) and c in WINDOW
		void	cls(WINDOW*& _hwnd = stdscr) const;		//clears the window and draws a border
		void	intro(WINDOW*& _hwnd = stdscr) const;	//display intro screen
		void	highScores(WINDOW*& _hwnd = stdscr)const;//display the top scores
		void	instructions(WINDOW*& _hwnd = stdscr)const;//display instructions
		void	endGame(EndEvent,WINDOW*& _hwnd = stdscr);	//eng game notify
		void	setName(WINDOW*& _hwnd = stdscr);		//sets players name
		void	settings(WINDOW*& _hwnd=stdscr);			//get/set setting
		void	setAttr(SettingSelect,WINDOW*& _hwnd=stdscr);			//set a given attribute
		void	feedSnake(WINDOW*& _hwnd = stdscr);		//feed the snake some food
		void	plantBomb(WINDOW*& _hwnd = stdscr);		//plant a bomb on the board
		void	printAtNode(listNode*,string,WINDOW*& _hwnd = stdscr)const;//print string at listNode (x,y)
		void	printAtNode(listNode*,char,WINDOW*& _hwnd = stdscr)const;//print char at listNode (x,y)
		void	load_settings(string _path = "jsnake.jss");//loads game settings
		void	save_settings(string _path = "jsnake.jss");//saves current game settings
		void	releaseKiller(WINDOW*& _hwnd = stdscr);//release the killers!
		void	specialSurprise(SpecialType,WINDOW*& _hwnd = stdscr);//place special food
		bool	inList(listNode*,listNode*,listList*) const;//sees if the listNode is in the listList (uses (x,y) coordinates)
		int		randInt(int _lower=1,int _upper=20) const;//returns a randomn number within bounds
		int		menu(WINDOW*& _hwnd = stdscr) const;	//display menu to user, return choice
		int		allTimeRank(string,int);				//searches for a matching name and score in list
		Point	nextPos(listNode*) const;				//return point of next relative position
		gameWindow	makeWin(string _caption="s1Lky sL1m",int _rows=10,int _cols=20, int _x=0,int _y=0,WINDOW*& _hwnd=stdscr) const;	//returns hwnd of new jSNake style window
		EndEvent	isCollision(listNode*,listNode*) const;		//checks to see if a collision has occured
		EndEvent	moveSnake(WINDOW*& _hwnd=stdscr);	//move snake a second time...maybe 5th?...errr....
		EndEvent	moveKiller(listNode*&,WINDOW*& _hwnd = stdscr);//move the killers(only one, do list in a loop, KISS)/return collision code
		EndEvent	run();								//start the game engine
		WINDOW*		stats(WINDOW*& _hwnd=stdscr) const;	//draws the stats bar during gameplay
		WINDOW*		gameParent() const;					//returns the game window parent hwnd according to settings and screen height/width
		WINDOW*		gameHwnd();							//returns the appropriate game window according to screen height/width and settings

		///////////////////////////////////////////////////////////////
		//	init			initialize the actual game play values
		//	…
		//	@return void
		///////////////////////////////////////////////////////////////
		void init()
		{
			listNode*	node;
			int		nH,//nW,
					iY,iX;

			Snake->delete_list();
			Food->delete_list();
			Bomb->delete_list();
			Special->delete_list();
			Killer->delete_list();

			Snake = new listList();
			Food = new listList();
			Bomb = new listList();
			Special = new listList();
			Killer = new listList();

			//build snake
			nH = NRows-2;


			//iX = X + 2;//1;
			//iY = nH/2 + Y; //this is relative to stdscr


			//snake starting position
			//relative to hwndGame
			iX = 2;
			iY = Height/2;


			for(int j=1; j<4; j++)
			{
				move(iY,iX);
				addch('X');
				node = new listNode(iX+j,iY);
				Snake->push_front(node);
				refresh();
			}

			Length = 0;
			Score = 0;
			Direction = 'd';
			Delay = 280;
			Collision = 0;
		}

		//getters
		int collision() const
		{return Collision;}

		int score() const
		{return Score;}
		
		int length() const
		{return Length;}

		int delay() const
		{return Delay;}
		
		wchar_t vborderc() const
		{return vBorder;}

		wchar_t hborderc() const
		{return hBorder;}

		wchar_t tlborderc() const
		{return tlBorder;}

		wchar_t trborderc() const
		{return trBorder;}

		wchar_t blborderc() const
		{return blBorder;}

		wchar_t brborderc() const
		{return brBorder;}

		char tailc() const
		{return TailC;}

		char bodyc() const
		{return BodyC;}

		char headc() const
		{return HeadC;}

		char foodc() const
		{return FoodC;}

		char bombc() const
		{return BombC;}

		char slowerc() const
		{return SlowerC;}

		char killerc() const
		{return KillerC;}

		char clearbadc() const
		{return ClearBadC;}

		char shrinkc() const
		{return ShrinkC;}

		int nrows() const
		{return NRows;}

		int ncols() const
		{return NCols;}

		string name() const
		{return Name;}

		int height() const
		{return Height;}

		int width() const
		{return Width;}

		int x() const
		{return X;}

		int y() const
		{return Y;}

		listList* snake() const
		{return Snake;}

		listList* food() const
		{return Food;}

		listList* bomb() const
		{return Bomb;}
		
		//setters
		void collision(int _collision)
		{Collision=_collision;}

		void score(int _score)
		{Score=_score;}

		void length(int _length)
		{Length = _length;}

		void delay(int _delay)
		{Delay = _delay;}

		void vborderc(wchar_t _border)
		{vBorder = _border;}
		
		void hborderc(wchar_t _border)
		{hBorder = _border;}

		void tlborderc(wchar_t _border)
		{tlBorder = _border;}

		void trborderc(wchar_t _border)
		{trBorder = _border;}

		void blborderc(wchar_t _border)
		{blBorder = _border;}

		void brborderc(wchar_t _border)
		{brBorder = _border;}

		void foodc(char _c)
		{FoodC = _c;}

		void bombc(char _c)
		{BombC = _c;}

		void headc(char _c)
		{HeadC = _c;}

		void tailc(char _c)
		{TailC = _c;}

		void bodyc(char _c)
		{BodyC = _c;}

		void slowerc(char _c)
		{SlowerC = _c;}

		void killerc(char _c)
		{KillerC = _c;}

		void clearbadc(char _c)
		{ClearBadC = _c;}

		void shrinkc(char _c)
		{ShrinkC = _c;}

		void nrows(int _y)
		{NRows = _y;}

		void ncols(int _x)
		{NCols = _x;}

		void name(string _name)
		{Name = _name;}

		void height(int _height)
		{Height = _height;}

		void width(int _width)
		{Width = _width;}

		void x(int _x)
		{X=_x;}

		void y(int _y)
		{Y=_y;}

		void snake(listList* &_snake)
		{Snake = _snake;}

		void food(listList* &_food)
		{Food = _food;}

		void bomb(listList* &_bomb)
		{Bomb = _bomb;}

};

#endif

