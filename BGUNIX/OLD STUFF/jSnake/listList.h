///////////////////////////////////////////////////////////////
// FILE NAME: 	listList.h         
// TITLE:         	listList Header File
// PROGRAMMER:  	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////
#ifndef LISTLIST_H
#define LISTLIST_H		//include guard

#include "listNode.h"	//include the listNode library

using namespace std;		//use the standard c++ library

class listList
{	
	private:
		listNode*	Head;	//head node of list

	public:
		listList()		//default constructor
		{Head=0;}

		~listList()		//default destructor
		{delete_list();}

		//class functions
		void push_front(listNode* &);	//push node to front of list
		void push_back(listNode* &);	//push node to back of list
		void pop_back();			//pop node from end of list
		void delete_node(listNode*&);	//remove the node from the list
		void delete_list();			//remove this list from memory
		int size() const;			//returns the size of the list
		listNode* tail() const;		//returns the tail node of a list

		//getter functions (inline)
		listNode* head() const		//return head node
		{return Head;}

		//setter functions (inline)
		void head(listNode* &_head)		//set head node
		{Head = _head;}
};

#endif


