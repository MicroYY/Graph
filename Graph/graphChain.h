#ifndef graphChain_
#define graphChain_

#include "chainWithIterator.h"
#include "chainNode.h"

using namespace std;

template<class T>
class graphChain :public chain<T>
{
public:
	T* eraseElement(int theVertex)
	{
		chainNode<T>* current = firstNode;
		chainNode<T>* trail = NULL;

		while (current != NULL&& current->element != theVertex)
		{
			trail = current;
			current = current->next;
		}
		//current为theVertex，trail为前一个

		//未找到匹配vertex
		if (current == NULL)
			return NULL;

		T* theElement = &current->element;
		if (trail != NULL)
			//正常情况，删除current
			trail->next = current->next;
		else
			//current就是第一个节点
			firstNode = current->next;

		delete current;
		listSize--;
		return theElement;
	}
};

#endif // !graphChain_
