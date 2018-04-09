#pragma once
//异常类

#include <string>
#include <iostream>

using namespace std;

//非法参数值
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

//非法输入数据
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

//非法索引
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

//矩阵索引越界
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

//矩阵大小不匹配
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

//stack栈为空
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

//queue队列为空
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

//hastTable哈希表已满
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

//边权重为定义
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

//method方法未定义
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