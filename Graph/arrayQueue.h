#pragma once
#include "queue.h"
#include "myExceptions.h"
#include <sstream>

using namespace std;


//location(i)=(location(队列首元素)+1）%arrayLength
//把队列映射为一个一维数组

template <class T>
class arrayQueue :public queue<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue()
	{
		delete[] queue;
	}

	bool empty() const
	{
		return theFront == theBack;
	}

	int size() const
	{
		return (theBack - theFront + arrayLength) % arrayLength;
	}
	T& front()
	{
		if (theFront == theBack)
			throw queueEmpty();
		return queue[(theFront + 1) % arrayLength];
	}
	T& back()
	{
		if (theFront == theBack)
			throw queueEmpty();
		return queue[theBack];
	}
	void pop()
	{
		if (theFront == theBack)
			throw queueEmpty();
		theFront = (theFront + 1) % arrayLength;
		queue[theFront].~T();
	}
	void push(const T& theElement);
private:
	int theFront;
	int theBack;
	int arrayLength;
	T* queue;
};

template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template <class T>
void arrayQueue<T>::push(const T& theElement)
{
	//如果需要增加数组长度
	if ((theBack + 1) % arrayLength == theFront)
	{
		T* newQueue = new T[2 * arrayLength];

		int start = (theFront + 1) % arrayLength;

		//没有形成环
		if (start < 2)
			copy(queue + start, queue + start + arrayLength - 1, newQueue);
		else
		{//队列形成环
			copy(queue + start, queue + arrayLength, newQueue);
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		queue = newQueue;
	}
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}