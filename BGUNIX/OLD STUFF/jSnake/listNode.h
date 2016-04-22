///////////////////////////////////////////////////////////////
// FILE NAME: 	listNode.h         
// TITLE:         	listNode Header File
// PROGRAMMER:  	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#ifndef LISTNODE_H
#define LISTNODE_H		//include guard

using namespace std;	//use the standard c++ library

class listNode			//class declaration
{
	private:
		int			X,	//x-coordinate
					Y;	//y-coordinate

		char		C;	//character to display

		listNode*	N;	//next node in a list

	public:
		listNode(int _x=10, int _y=10, char _c=(char)(221))	//constructor
		{
			X=_x;	//default x
			Y=_y;	//default y
			C=_c;	//default display char
			N=0;	//point to null
		}

		void operator=(const listNode& _node)			//overload ='s for setting (x,y) only
		{
			X = _node.x();
			Y = _node.y();
		}

		bool operator==(const listNode& _node) const		//oveload =='s for comparing (x,y)s
		{
			if((_node.x() == X) && (_node.y() == Y))
				return true;
			else
				return false;
		}

		//not overloading operator!= because i need that to work with the actual memory addresses, (x,y)s will be same

		//getters
		int x() const
		{return X;}

		int y() const
		{return Y;}

		char c() const
		{return C;}

		listNode* n() const
		{return N;}

		//setters
		void x(int _x)
		{X=_x;}

		void y(int _y)
		{Y=_y;}

		void c(char _c)
		{C=_c;}

		void n(listNode* _n)
		{N=_n;}
};

#endif


