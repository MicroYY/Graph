//创建2维数组，分配内存失败时不抛异常

#ifndef make2dArrayNoCatch_
#define make2dArrayNoCatch_

using namespace std;

template <class T>
void make2dArray(T** &x, int numberOfRows, int numberOfColumns)
{//创建一个二维数组
	x = new T*[numberOfRows];
	for (int i = 0; i < numberOfRows; i++)
		x[i] = new T[numberOfColumns];
}


#endif // !make2dArrayNoCatch_

