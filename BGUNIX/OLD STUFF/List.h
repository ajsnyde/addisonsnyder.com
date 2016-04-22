#pragma once
#include "animShapeO.h"
#include "Link.h"


template <class T>
class List
{
public:
	List(void);
	~List(void);
	//void append(T);
	void add(animShapeO);
protected:
	Link<T> head();
	Link<T> tail();
	Link<T> * it;
	int length;
};
