//É¾³ý¶þÎ¬Êý×é

#ifndef delete2dArray_
#define delete2dArray_

using namespace std;

template <class T>
void delete2dArray(T** &theArray, int numberOfRows)
{
	for (int i = 0; i < numberOfRows; i++)
		delete[] theArray[i];
	delete[] theArray;
	theArray = 0;
}


#endif // !delete2dArray

