//����2ά���飬�����ڴ�ʧ��ʱ�����쳣

#ifndef make2dArrayNoCatch_
#define make2dArrayNoCatch_

using namespace std;

template <class T>
void make2dArray(T** &x, int numberOfRows, int numberOfColumns)
{//����һ����ά����
	x = new T*[numberOfRows];
	for (int i = 0; i < numberOfRows; i++)
		x[i] = new T[numberOfColumns];
}


#endif // !make2dArrayNoCatch_

