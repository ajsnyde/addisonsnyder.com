///////////////////////////////////////////////////////////////
// FILE NAME: 	scoresNode.h         
// TITLE:         	scoresNode Header File
// PROGRAMMER:  	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////
#ifndef SCORESNODE_H
#define SCORESNODE_H

#include <string>
#include <iostream>

using namespace std;

class scoresNode
{
	private:

		string		Name;		//player's name
		int		Score;		//player's score
		int		Length;	//final snake length
		bool		HighFive;	//is this record in top 5
		scoresNode*	Next;		//the next node in a list of scoresNode's

	public:

		scoresNode(string _name="\0",int _score=0,int _length=0,bool _hi5=false,scoresNode* _next=0)	//default/overloaded constructor
		{
			//set default values
			Name = _name;
			Score = _score;
			Length = _length;
			HighFive = _hi5;
			Next = _next;
		}

		//setter functions (inline)
		void name(string _name)
		{Name = _name;}

		void score(int _score)
		{Score = _score;}

		void length(int _length)
		{Length = _length;}

		void hi5(bool _hi5)
		{HighFive = _hi5;}

		void next(scoresNode* _next)
		{Next = _next;}

		//getter functions (inline)
		string name() const
		{return Name;}

		int score() const
		{return Score;}

		int length() const
		{return Length;}

		bool hi5() const
		{return HighFive;}

		scoresNode* next() const
		{return Next;}

		//class functions (inline)

		void print() const	//display this node's contents
		{
			//convert this to curses.h output for final project,
			//using stdio for now
			cout << "\tName: " << Name << endl;
			cout << "\tScore: " << Score << endl;
			cout << "\tLength: " << Length << endl;
			cout << "\tTop 5?: " << (HighFive?"Yes":"No") << endl;
			cout << "\tAddres: " << this << endl;
			cout << "\tNext: " << Next << endl;
		}
};

#endif

