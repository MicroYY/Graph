//最大优先队列的heap实现

#ifndef maxHeap_
#define maxHeap_

#include "maxPriorityQueue.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>
#include <algorithm>

using namespace std;

template<class T>
class maxHeap :public maxPriorityQueue<T>
{
public:
	maxHeap(int initialCapacity = 10);
	~maxHeap() { delete[] heap; }
	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }
	const T& top()
	{
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void deactivateArray()
	{
		heap = NULL;
		arrayLength = heapSize = 0;
	}
	void output(ostream& out) const;

private:
	int heapSize;			//队列中实际存储的元素数
	int arrayLength;		//capacity+1
	T* heap;				//heap[0]为空，不存放元素
							//元素存放索引为1-heapSize-arrayLength
};

template<class T>
maxHeap<T>::maxHeap(int initialCapacity)
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
void maxHeap<T>::push(const T& theElement)
{
	if (heapSize == arrayLength - 1)
	{
		changeLength1D(heap, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	int currentNode = ++heapSize;
	//将新元素插入尾部，从新节点到根节点进行冒泡
	//currentNode/2为currentNode的父节点索引
	//新节点与其父节点进行比较，若父节点更大，过着到达树根，则跳出循环
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

//删除根节点的元素
template<class T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
		throw queueEmpty();

	//删除根节点，即最大的元素
	heap[1].~T();

	T lastElement = heap[heapSize--];

	int currentNode = 1;
	int child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
			//用一个父节点的两个子节点比较，选出较大的
			child++;

		//如果最后一个节点比选出来的大，结束循环
		if (lastElement >= heap[child])
			break;

		//如果最后一个节点更小，进行冒泡操作
		heap[currentNode] = heap[child];
		currentNode = child;
	}
}

//用theHeap[1:theSize]初始化maxHeap
template<class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	//从最后一个有孩子的节点开始检查
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		int child = 2 * root;
		while (child <= heapSize)
		{
			//选出子节点中较大的与根节点比较
			if (child < heapSize && heap[child] < heap[child + 1])
				child++;
			if (rootElement > heap[child])
				break;
			//若孩子节点更大，父节点变为孩子节点的值
			heap[child / 2] = heap[child];
			//下移，当前孩子节点作为下一次循环的父节点
			child *= 2;
		}
		heap[child / 2] = rootElement; 
		//以root为跟的子树已经转为大根堆
	}
}

template<class T>
void maxHeap<T>::output(ostream& out) const
{
	copy(heap + 1, heap + heapSize + 1, ostream_iterator<T>(cout, " "));
}

template<class T>
ostream& operator<<(ostream& out, const maxHeap<T>& x)
{
	x.output(out);
	return out;
}


#endif // !maxHeap_
