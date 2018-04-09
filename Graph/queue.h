#pragma once
//������queue

using namespace std;

template <class T>
class queue
{
public:
	virtual ~queue() {}

	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual T& front() = 0;
	//���ص�һ��Ԫ�ص�����
	virtual T& back() = 0;
	//�������һ��Ԫ�ص�����
	virtual void pop() = 0;
	//ɾ����һ��Ԫ��
	virtual void push(const T& theElement) = 0;
	//�ڶ���ĩβ����theElement
};