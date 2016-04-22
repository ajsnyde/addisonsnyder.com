///////////////////////////////////////////////////////////////
// FILE NAME:		todo.h
// TITLE:		To-Do Header File
// PROGRAMMER:  	Addison Snyder
// FOR COURSE:    	CS 3350
// DUE DATE:      	9/22/2014
//
// ALL CODE IS MINE UNLESS OTHERWISE NOTED
///////////////////////////////////////////////////////////////

#pragma once
#include "string"

using namespace std;

class todo {
	public:
	todo(); // constructor!
	todo(int, string);//overloaded constructor
	void display();//all member functions (getters, setters, displayers..)
	int get_id();	//ID IS NOT USED YET, BUT IS PROVIDED FOR FUTURE USE
	int get_priority();
	string get_info();
	void set_id(int);
	void set_priority(int);
	void set_info(string);

	private://private variables
	int id;
	int priority;
	string info;
};
