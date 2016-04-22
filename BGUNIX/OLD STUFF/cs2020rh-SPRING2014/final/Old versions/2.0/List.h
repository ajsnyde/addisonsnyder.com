///////////////////////////////////////////////////////////////
// FILE NAME:		List.h
// TITLE:		List Header File
// PROGRAMMER:  	Addison Snyder
// FOR COURSE:    	CS 2020
// DUE DATE:      	4/28/2014
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#ifndef LIST_H
#define LIST_H
#include "string"
#include "Car.h"

using namespace std;


class List
{

private:
	Car* head;
public:
	List(void);
	~List(void);
	void addcar();//adds car to the end of list.
	void insertcar(int);//inserts car at point (specified by parameter)
	void killcar(int);//sends car to the junkyard. :[
	void displayall();//displays cars in order (head first)
	Car* getcar(int);//returns pointer for nth car
};

#endif
