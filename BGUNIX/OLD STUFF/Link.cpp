#include "Link.h"

template <class T>
Link<T>::Link(void)
{
	next = 0;
	prev = 0;
}

template <class T>
Link<T>::~Link(void)
{
}

template <class T>
void Link<T>::setdata(T input)
{
	data = input;
}

template <class T>
void Link<T>::setprev(Link<T> * input)
{
	prev = input;
}

template <class T>
void Link<T>::setnext(Link<T> * input)
{
	next = input;
}
