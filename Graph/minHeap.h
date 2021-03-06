#pragma once
#include "minPriorityQueue.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

template <class T>
class minHeap : public minPriorityQueue<T>
{
public:
	minHeap(int initialCapacity = 10);
	~minHeap()
	{
		delete[] heap;
	}
	bool empty() const
	{
		return heapSize == 0;
	}
	int size() const
	{
		return heapSize;
	}
	const T& top()
	{
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T *, int);
	void deactivateArray()
	{
		heap = NULL; arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;

private:
	int heapSize;			//队列中的已有元素数
	int arrayLength;		//capacity+1
	T* heap;				//元素数组,heap[0]为空
};

template<class T>
minHeap<T>::minHeap(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<class T>
void minHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;
	//currentNode/2 父节点索引
	while (currentNode != 1 && heap[currentNode / 2] > theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

template <class T>
void minHeap<T>::pop()
{
	if (heapSize == 0)
		throw queueEmpty();

	heap[1].~T();

	T lastElement = heap[heapSize--];

	int currentNode = 1;
	int child = 2;
	while (child <= heapSize)
	{//同一个父节点的两个子节点比较
		if (child < heapSize && heap[child] > heap[child + 1])
			child++;

		//最后一个元素与两个子节点比较，小于则结束
		if (lastElement <= heap[child])
			break;

		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template <class T>
void minHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	//从最后一个具有孩子的节点开始检查
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		int child = 2 * root;

		while (child <= heapSize)
		{
			if (child < heapSize && heap[child] > heap[child + 1])
				child++;

			if (rootElement <= heap[child])
				break;

			heap[child / 2] = heap[child];
			//移到下一层 直到没有子节点
			child *= 2;
		}
		heap[child / 2] = rootElement;
	}
}

template<class T>
void minHeap<T>::output(ostream& out) const
{// Put the array into the stream out.
	copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, "  "));
}

template<class T>
ostream& operator<<(ostream& out, const minHeap<T>& x)
{
	x.output(out);
	return	out;
}