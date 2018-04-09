#pragma once
//�쳣��

#include <string>
#include <iostream>

using namespace std;

//�Ƿ�����ֵ
class illegalParameterValue
{
public:
	illegalParameterValue(string theMessage = "Illegal parameter value")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//�Ƿ���������
class illegalInputData
{
public:
	illegalInputData(string theMessage = "Illegal data input")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//�Ƿ�����
class illegalIndex
{
public:
	illegalIndex(string theMessage = "Illegal index")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//��������Խ��
class matrixIndexOutOfBounds
{
public:
	matrixIndexOutOfBounds(string theMessage = "Matrix index out of bounds")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//�����С��ƥ��
class matrixSizeMismatch
{
public:
	matrixSizeMismatch(string theMessage = "The size of the two matrics doesn't match")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//stackջΪ��
class stackEmpty
{
public:
	stackEmpty(string theMessage = "Invalid operation on empty stack")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//queue����Ϊ��
class queueEmpty
{
public:
	queueEmpty(string theMessage = "Invaild operatoin on empty queue")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//hastTable��ϣ������
class hashTableFull
{
public:
	hashTableFull(string theMessage = "The hash table is full")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//��Ȩ��Ϊ����
class undefinedEdgeWeight
{
public:
	undefinedEdgeWeight(string theMessage = "No edge weights defined")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};

//method����δ����
class undefinedMethod
{
public:
	undefinedMethod(string theMessage = "This method is undefined")
	{
		message = theMessage;
	}
	void outputMessage()
	{
		cout << message << endl;
	}
private:
	string message;
};