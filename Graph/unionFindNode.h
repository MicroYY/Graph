#pragma once
using namespace std;

struct  unionFindNode
{
	int parent;
	bool root;
	unionFindNode()
	{
		parent = 1;
		root = true;
	}
};