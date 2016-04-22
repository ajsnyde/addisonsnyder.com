#pragma once
template <class T>
class Link
{
public:

	Link(void);
	~Link(void);
	void setdata(T);
	void setprev(Link<T> *);
	void setnext(Link<T> *);

protected:
	T data;
	Link<T> * next;
	Link<T> * prev;
};
