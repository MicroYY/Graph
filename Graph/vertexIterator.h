#pragma once
//³éÏóÀà graph vertex iterator

using namespace std;

template <class T>
class vertexIterator
{
public:
	virtual ~vertexIterator() {}
	virtual int next() = 0;
	virtual int next(T&) = 0;
};