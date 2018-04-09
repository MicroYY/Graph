//������ȶ��е�heapʵ��

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
	int heapSize;			//������ʵ�ʴ洢��Ԫ����
	int arrayLength;		//capacity+1
	T* heap;				//heap[0]Ϊ�գ������Ԫ��
							//Ԫ�ش������Ϊ1-heapSize-arrayLength
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
	//����Ԫ�ز���β�������½ڵ㵽���ڵ����ð��
	//currentNode/2ΪcurrentNode�ĸ��ڵ�����
	//�½ڵ����丸�ڵ���бȽϣ������ڵ���󣬹��ŵ���������������ѭ��
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}
	heap[currentNode] = theElement;
}

//ɾ�����ڵ��Ԫ��
template<class T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
		throw queueEmpty();

	//ɾ�����ڵ㣬������Ԫ��
	heap[1].~T();

	T lastElement = heap[heapSize--];

	int currentNode = 1;
	int child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
			//��һ�����ڵ�������ӽڵ�Ƚϣ�ѡ���ϴ��
			child++;

		//������һ���ڵ��ѡ�����Ĵ󣬽���ѭ��
		if (lastElement >= heap[child])
			break;

		//������һ���ڵ��С������ð�ݲ���
		heap[currentNode] = heap[child];
		currentNode = child;
	}
}

//��theHeap[1:theSize]��ʼ��maxHeap
template<class T>
void maxHeap<T>::initialize(T* theHeap, int theSize)
{
	delete[] heap;
	heap = theHeap;
	heapSize = theSize;

	//�����һ���к��ӵĽڵ㿪ʼ���
	for (int root = heapSize / 2; root >= 1; root--)
	{
		T rootElement = heap[root];

		int child = 2 * root;
		while (child <= heapSize)
		{
			//ѡ���ӽڵ��нϴ������ڵ�Ƚ�
			if (child < heapSize && heap[child] < heap[child + 1])
				child++;
			if (rootElement > heap[child])
				break;
			//�����ӽڵ���󣬸��ڵ��Ϊ���ӽڵ��ֵ
			heap[child / 2] = heap[child];
			//���ƣ���ǰ���ӽڵ���Ϊ��һ��ѭ���ĸ��ڵ�
			child *= 2;
		}
		heap[child / 2] = rootElement; 
		//��rootΪ���������Ѿ�תΪ�����
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
