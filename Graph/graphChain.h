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
		//currentΪtheVertex��trailΪǰһ��

		//δ�ҵ�ƥ��vertex
		if (current == NULL)
			return NULL;

		T* theElement = &current->element;
		if (trail != NULL)
			//���������ɾ��current
			trail->next = current->next;
		else
			//current���ǵ�һ���ڵ�
			firstNode = current->next;

		delete current;
		listSize--;
		return theElement;
	}
};

#endif // !graphChain_
