#include "Link.h"


template <class T>
List<T>::List(void)
{
	head.next = &tail;
	tail.prev = &head;
	it = &head;
	length = 0;
}

template <class T>
List<T>::~List(void)
{
}

void List<T>::add(animShapeO in)
{
	cout << "it works!";
}

/*
template <class T>
void List<T>::append(T & in)
{

	Link<T> input;
	input.setdata(in);

	Link<T> * temp = (*tail).prev;
	temp.next = new Link<T>;
	*(temp.next) = input;
	(*(temp.next)).prev = temp;
	(*(temp.next)).next = &tail;
	tail.prev = temp;

}
*/