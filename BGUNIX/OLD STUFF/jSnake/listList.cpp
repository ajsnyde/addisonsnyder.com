///////////////////////////////////////////////////////////////
// FILE NAME: 	listList.cpp        
// TITLE:         	listList Implementation File
// PROGRAMMER:	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#include "listList.h"

using namespace std;

///////////////////////////////////////////////////////////////
//	push_front			add node to front of list
//	@param _work	listNode*&	the node to add to the list
//	…
//	@return void
///////////////////////////////////////////////////////////////
void listList::push_front(listNode* &_work)
{
	if(Head)
		//list is not empty
		_work->n(Head);		//set incoming node's next pointer to current head
	else
		_work->n(0);			//this is first node so set next to NULL

	Head = _work;				//set head to incoming node
}

///////////////////////////////////////////////////////////////
//	push_back			add node to back of list
//
//	@param _work	listNode*&	the node to add to the list
//	…
//	@return void
///////////////////////////////////////////////////////////////
void listList::push_back(listNode* &_work)
{
	listNode	*temp = tail();	//get tail node

	_work->n(0);
	temp->n(_work);
}

///////////////////////////////////////////////////////////////
//	pop_back				remove a node from the end of list
//	…
//	@return void
///////////////////////////////////////////////////////////////
void listList::pop_back()
{
	listNode	*temp = Head,
			*prev = 0;

	if(temp)
	{
		//list is not empty, check if first node is last node
		if(temp->n())
		{
			//first node is not the last node
			//go through list until last node is found

			while(temp->n())
			{
				prev = temp;
				temp = temp->n();	//advance temp until end of the list is reached
			}

			prev->n(0);			//make prev the new end of list
			delete temp;			//remove the last node in the list from memory
		}
		else
		{
			//first node is also the last node in the list
			delete Head;
			Head = 0;
		}
	}
	else
	{
		//list is empty
		Head = 0;		//set Head to null
	}
}

///////////////////////////////////////////////////////////////
//	delete_node						remove a node from the list
//	@param _node	listNode*&	the node to delete
//	…
//	@return void
///////////////////////////////////////////////////////////////
void listList::delete_node(listNode*& _node)
{
	listNode	*temp = Head,		//start at beginning of list
				*prev = temp;
				
	while(temp)
	{
		//traverse list while not empty
		if(*temp==*_node)
		{
			//found a match
			if(*temp==*Head)
			{
				//match at list head
				Head = temp->n();	//move head to next node
				delete temp;		//delete node
				return;				//only delete 1 match (remove this line to remove all)
			}
			else
			{
				//in body or tail
				prev->n(temp->n());	//set prev next to temp's next node
				delete temp;		//delete the node
				temp = prev;		//move temp back to prev (because moving temp forward below)
				return;				//only delete 1 match (remove this line to remove all)
			}
		}
		else
		{
			//did not find a match with this node
		}

		if(temp)
		{
			prev = temp;		//set prev node
			temp = temp->n();	//examine next node
		}
		else
			temp=prev=Head;		//start at head of list again
	
	}	//end loop/fall off list
}

///////////////////////////////////////////////////////////////
//	delete_list			remove this list from memory
//	…
//	@return void
///////////////////////////////////////////////////////////////
void listList::delete_list()
{
	listNode	*temp = Head,
			*next = 0;

	while(temp)
	{
		next = temp->n();	//set next to the next node
		delete temp;		//delete current node
		temp = next;		//examine next node
	}

	Head = 0;			//set Head to null
}

///////////////////////////////////////////////////////////////
//	size				returns the size of the list
//	…
//	@return int
///////////////////////////////////////////////////////////////
int listList::size() const
{
	int 		count = 0;	//counting variable
	listNode*	temp = Head;	//start at head of list

	while(temp)
	{
		count++;
		temp=temp->n();
	}

	return count;
}

///////////////////////////////////////////////////////////////
//	tail			return pointer to last listNode in listList
//	…
//	@return listNode*
///////////////////////////////////////////////////////////////
listNode* listList::tail() const
{
	listNode	*temp = Head;	//start at beginning of list

	while(temp->n())
		temp = temp->n();

	return temp;
}

