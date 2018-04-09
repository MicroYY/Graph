#pragma once
//抽象类queue

using namespace std;

template <class T>
class queue
{
public:
	virtual ~queue() {}

	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual T& front() = 0;
	//返回第一个元素的引用
	virtual T& back() = 0;
	//返回最后一个元素的引用
	virtual void pop() = 0;
	//删除第一个元素
	virtual void push(const T& theElement) = 0;
	//在队列末尾插入theElement
};