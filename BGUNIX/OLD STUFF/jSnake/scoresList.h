///////////////////////////////////////////////////////////////
// FILE NAME: 		scoresList.h         
// TITLE:         	scoresNode Header File
// PROGRAMMER:  		Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#ifndef SCORESLIST_H
#define SCORESLIST_H

#include "scoresNode.h"
#include <fstream>

using namespace std;

class scoresList
{
	private:
		scoresNode*		Head;	//pointer to the first node in list

	public:
		scoresList(scoresNode* _head = 0)	//"default"/overloaded constructor (inline)
		{Head = _head;}

		~scoresList()						//destructor (inline)
		{delete_list();}	


		scoresList(const scoresList& _right)//copy constructor (inline)
		{
			scoresNode	*traverse,
						*newNode;
			string		_name;
			int			_score,
						_length;
			bool		_hi5;
			
			traverse = _right.head();		//start at head of incoming list

			Head=0;

			while(traverse)
			{
				//get current node values
				_name = traverse->name();
				_score = traverse->score();
				_length = traverse->length();
				_hi5 = traverse->hi5();
				newNode = new scoresNode(_name,_score,_length,_hi5);	//reserve memory
				append(newNode);//add new memmory to list
				traverse = traverse->next();//examine next node
			}
		}		//end copy constructor

		//overloads
		scoresList& operator=(const scoresList& _right)
		{
			scoresNode	*traverse,
						*newNode;
			string		_name;
			int			_score,
						_length;
			bool		_hi5;


			if(this == &_right)				//args are the same object
				return *this;

			delete_list();					//delete list
			
			traverse = _right.head();		//start at head of incoming list

			while(traverse)
			{
				//get current node values
				_name = traverse->name();
				_score = traverse->score();
				_length = traverse->length();
				_hi5 = traverse->hi5();

				newNode = new scoresNode(_name,_score,_length,_hi5);	//reserve memory with values

				append(newNode);//add new memmory to list

				traverse = traverse->next();//examine next node
			}

			return *this;

		}

		//operator >
		bool operator>(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize>rsize)
				return true;
			else
				return false;
		}

		//operator <
		bool operator<(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize<rsize)
				return true;
			else
				return false;
		}

		//operator ==
		bool operator==(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize==rsize)
				return true;
			else
				return false;
		}

		//operator >
		bool operator!=(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize!=rsize)
				return true;
			else
				return false;
		}

		//operator >=
		bool operator>=(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize>=rsize)
				return true;
			else
				return false;
		}

		//operator <=
		bool operator<=(const scoresList& _right)
		{
			int rsize,
				lsize;

			rsize = _right.size();
			lsize = size();
			
			if(lsize<=rsize)
				return true;
			else
				return false;
		}

		//operator +
		scoresList& operator+(const scoresList& _right)
		{
			scoresList	*newList = new scoresList;
			scoresNode	*traverse,
						*newNode;
			string	_name;
			int		_score,
					_length;
			bool	_hi5;

			traverse = Head;

			while(traverse)
			{
				//traverse left list
				//get values
				_name = traverse->name();
				_score = traverse->score();
				_length = traverse->length();
				_hi5 =	traverse->hi5();

				newNode = new scoresNode(_name,_score,_length,_hi5);	//reserve space with values

				newList->append(newNode);		//add new memory to list

				traverse = traverse->next();	//examine next element
			}

			traverse = _right.head();			//beginning of right list

			while(traverse)
			{
				//traverse right list
				//get values
				_name = traverse->name();
				_score = traverse->score();
				_length = traverse->length();
				_hi5 =	traverse->hi5();

				newNode = new scoresNode(_name,_score,_length,_hi5);	//reserve space with value

				newList->append(newNode);		//add new memory to list

				traverse = traverse->next();	//examine next element
			}

			return *newList;
		}

		//class functions
		void sort();							//do seletion sort on high scores
		void append(scoresNode*&,bool _front=false);//add a node to the list, front or back
		void insert(scoresNode*&);				//insert a node in a list according to score
		void delete_node(scoresNode*&);			//delete a particular node the list
		void delete_list();						//delete a list from memory
		void setHi5();							//goes through list and sets the node's hi5 values
		void display() const;					//displays the list's contents
		int size() const;						//returns size of list
		scoresNode* tail() const;				//returns the tail of list
		void load_records(string _path = "jsnake.jsr");	//loads path into list[jsnake.jsr]
		void save_records(string _path = "jsnake.jsr");	//saves current list[jsnake.jsr]

		//setter functions (inline)
		void head(scoresNode* &_head)
		{Head = _head;}

		//getter functions (inline)
		scoresNode* head() const
		{return Head;}
};


#endif

