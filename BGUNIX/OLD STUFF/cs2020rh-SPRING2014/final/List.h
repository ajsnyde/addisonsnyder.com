#ifndef LIST_H
#define LIST_H

#include "Car.h"

class List
{
private:
	Car *head;

public:
	List();
	List(const List&);
	~List();
	const List operator=(const List&);
	void add(string, string, string, string, string, int, int, int, bool);
	void ins(int, string, string, string, string, string, int, int, int, bool);
	void del(int);
	void displaylist();
	void load(List);
};

#endif 