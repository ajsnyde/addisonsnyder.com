///////////////////////////////////////////////////////////////
// FILE NAME: 	scoresList.cpp        
// TITLE:         	scoresList Implementation File
// PROGRAMMER:	Jacob Boggs
// FOR COURSE:    	CS2020
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////
#include "scoresList.h"

using namespace std;

///////////////////////////////////////////////////////////////
//	sort		selection sort on list for high score
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::sort()
{
	int		intTempMax = 0,
			intMax = 0,
			intCurMax = 0;

	scoresNode	*outer = Head,				//start at beginning of list
			*max = 0,
			*inner = 0,
			*temp = 0,
			*prevOuter = 0,
			*prevInner = 0,
			*prevMax = 0;

	while(outer)
	{
		//go through list until at last node
	
		inner = outer->next();				//set inner node to next node
		max = prevInner = prevMax = outer;			//set max node to current node
		intMax =  outer->score();
		intCurMax = outer->score();		//set max values to current value

		while(inner)
		{
			//compare outer node to rest of nodes in list
			
			intTempMax = inner->score();		//set max score to current comparison node

			if(intCurMax < intTempMax)
			{
				//a higher value was found

				intCurMax = intTempMax;		//set new max value
				
				prevMax = prevInner;			//set prev max to prev inner node
				max = inner;				//set the max node to the current node
			}

			prevInner = inner;				//set prev inner node
			inner = inner->next();			//compare outer node to next inner node
		}

		//now we are through comparing and max node is
		//the node with the highest score (if actually found)
		
		if(intMax < intCurMax)
		{
			//a new max was found so swap the nodes
			
			if(outer==Head)
			{
				//swapping with the head node

				temp = outer;
				inner = max->next();

				if(temp->next()==max)
				{
					//max obj is second in list; head = swapping
					temp->next(max->next());
					max->next(temp);
					Head = outer = max;
				}
				else
				{
					//max obj is not second in list; head = swapping
					max->next(temp->next());
					temp->next(inner);
					prevMax->next(temp);
					Head = outer = max;
				}
			}
			else
			{
				//swapping with node that is not the head node
				
				temp = outer;
				inner = max->next();
				prevOuter->next(max);
				max->next(temp);
				prevMax->next(inner);
				prevOuter->next(max);
				outer = max;
			}
		}
		else
		{
			//no new max found
		}

		prevOuter = outer;		//set prev outer node
		outer = outer->next();	//go to next outer node
	}
}

///////////////////////////////////////////////////////////////
//	append				add a node to the list
//	@param _node	scoresNode*&	the node to add to the list
//	@param _front	bool		append to front or back of list
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::append(scoresNode* &_node, bool _front)
{
	scoresNode	*temp = Head;		//start at head of list

	if(temp)
	{
		//list is not empty
	
		if(_front)
		{
			//add node to front of list
			_node->next(Head);
			Head = _node;
		}
		else
		{
			//add node to end of list
			
			while(temp->next())			//find end of list
				temp = temp->next();

			temp->next(_node);			//point last node to new last node
			_node->next(0);			//point last nodes next to NULL
		}
	}
	else
	{
		//list is empty
		Head = _node;
	}
}

///////////////////////////////////////////////////////////////
//	insert				insert a node into a list according to acore
//	@param _node	scoresNode*&	the node to insert
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::insert(scoresNode* &_node)
{
	scoresNode	*temp = Head,		//start at beginning of list
			*prev = 0;

	int		itemp=0,
			inode=0;

	if(temp)
	{
		//list is not empty
		itemp = temp->score();
		inode = _node->score();
		while((itemp > inode) && temp->next())
		{
			//traverse list until temp score is not greater than the _node score,
			///or until the end of the list is reached
			prev = temp;
			temp = temp->next();
		}

		//at head, at end, or lower score has been found
		itemp = temp->score();
		inode = _node->score();
		if(itemp < inode)
		{
			//found a smaller value
			if(temp==Head)
			{
				//temp has a lesser value and is head
				_node->next(Head);
				Head = _node;
			}
			else
			{
				//temp has lesser value and is not head
				prev->next(_node);
				_node->next(temp);
			}
		}
		else
		{
			//searched through the list and did not find a lower value,
			//add _node to end of list
			temp->next(_node);
			_node->next(0);
		}
	}
	else
	{
		//list is empty
		Head = _node;			//set Head to _node
		_node->next(0);					
	}
}

///////////////////////////////////////////////////////////////
//	delete_node				remove a node from the list
//	@param _node	scoresNode*&		the node to delete
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::delete_node(scoresNode*& _node)
{
	scoresNode	*temp = Head,		//start at beginning of list
				*prev = temp;
				
	while(temp)
	{
		//traverse list while not empty
		if(temp==_node)
		{
			//found a match
			if(temp==Head)
			{
				//match at list head
				Head = temp->next();	//move head to next node
				delete temp;		//delete node
			}
			else
			{
				//in body or tail
				prev->next(temp->next());	//set prev next to temp's next node
				delete temp;		//delete the node
				temp = prev;		//move temp back to prev (because moving temp forward below)
			}
		}
		else
		{
			//did not find a match with this node
		}

		if(temp)
		{
			prev = temp;		//set prev node
			temp = temp->next();//examine next node
		}
		else
			temp=prev=Head;		//start at head of list again
	
	}	//end loop/fall off list
}

///////////////////////////////////////////////////////////////
//	delete_list			remove a list from memory
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::delete_list()
{
	scoresNode	*temp = Head,		//start at head of list
				*nextNode = 0;

	while(temp)
	{
		nextNode = temp->next();
		delete temp;
		temp = nextNode;
	}

	Head = 0;
}

///////////////////////////////////////////////////////////////
//	setHi5				goes through list and sets the hi5 values
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::setHi5()
{
	scoresNode	*temp = 0;

	sort();				//make sure the list is sorted

	temp = Head;				//start at beginning of list

	for(int j=0; j<size(); j++)		//set first 5 values to true, rest to false
	{
		if(temp)
		{
			switch(j)
			{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
					temp->hi5(true);
					break;

				default:
					temp->hi5(false);
					break;
			}

			temp = temp->next();	//examine next node
		}
	}
}
///////////////////////////////////////////////////////////////
//	display			display the list's contents
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::display() const
{
	scoresNode	*temp = Head;		//start at beginning of list

	while(temp)
	{
		temp->print();
		cout << endl;
		temp=temp->next();
	}
}

///////////////////////////////////////////////////////////////
//	size					returns size of list
//	…
//	@return count	int
///////////////////////////////////////////////////////////////
int scoresList::size() const
{
	scoresNode	*temp = Head;
	int			count = 0;

	while(temp)
	{
		count++;
		temp=temp->next();
	}

	return count;
}

///////////////////////////////////////////////////////////////
//	tail				returns tail of list
//	…
//	@return scoresNode*
///////////////////////////////////////////////////////////////
scoresNode* scoresList::tail() const
{
	scoresNode	*temp = Head;	//start at beginning of list

	while(temp->next())
		temp = temp->next();
	
	return temp;
}

///////////////////////////////////////////////////////////////
//	load_records		loads file into list [jsnake.jsr]
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::load_records(string _path)
{
	fstream	file;
	scoresNode	*temp;
	string	sresult="\0";

	file.open(_path.c_str(),ios::in);

	if(file)
	{
		//file is good

		getline(file,sresult);	//seed loop

		while(file.good())
		{
			
			if((sresult!="*****") && (sresult !="\0"))
			{
				temp = new scoresNode();//reserve space for new entry
			
				temp->name(sresult);					//name
				getline(file,sresult);	//get next line
				temp->score(atoi(sresult.c_str()));		//score
				getline(file,sresult);	//get next line
				temp->length(atoi(sresult.c_str()));	//length
				getline(file,sresult);	//get next line
				temp->hi5(atoi(sresult.c_str()));		//high five

				append(temp);			//insert new node into list
			}

			getline(file,sresult);		//get next line
		}//file not good
	}

	file.close();	//close file
}

///////////////////////////////////////////////////////////////
//	save_records		saves list to file [jsnake.jsr]
//	…
//	@return void
///////////////////////////////////////////////////////////////
void scoresList::save_records(string _path)
{
	fstream	file;
	scoresNode	*temp=Head;	//start at beginning of list

	file.open(_path.c_str(),ios::out);	//open file for output/dont append
	if(file)
	{
		//opened successfully
		while(temp)
		{
			file << temp->name() << endl;	//name
			file << temp->score() << endl;	//score
			file << temp->length() << endl;	//length
			file << temp->hi5() << endl;	//hi5
			file << "*****" << endl;		//record separator
			
			temp = temp->next();	//next node
		}
	}

	file.close();
}






