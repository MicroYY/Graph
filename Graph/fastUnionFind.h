#pragma once

#include <iostream>
#include "unionFindNode.h"

using namespace std;

class fastUnionFind
{
public :
	fastUnionFind(int numberOfElement)
	{
		node = new unionFindNode[numberOfElement + 1];
	}

	void unite(int rootA, int rootB)
	{
		if (node[rootA].parent < node[rootB].parent)
		{
			node[rootB].parent += node[rootA].parent;
			node[rootA].root = false;
			node[rootA].parent = rootB;
		}
		else
		{
			node[rootA].parent += node[rootB].parent;
			node[rootB].root = false;
			node[rootB].parent = rootA;
		}
	}

	int find(int theElement)
	{
		int theRoot = theElement;
		while (!node[theRoot].root)
			theRoot = node[theRoot].parent;

		int currentNode = theElement;
		while (currentNode != theRoot)
		{
			int parentNode = node[currentNode].parent;
			node[currentNode].parent = theRoot;
			currentNode = parentNode;
		}
		return theRoot;
	}

protected:
	unionFindNode* node;
};