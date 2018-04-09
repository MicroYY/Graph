#include <iostream>
#include "arrayQueue.h"
#include "myExceptions.h"

using namespace std;

int main(void)
{
	arrayQueue<int> q(4);

	q.push(1);
	cout << "Queue front is " << q.front() << endl;
	cout << "Queue rear is " << q.back() << endl;
	q.push(2);
	cout << "Queue front is " << q.front() << endl;
	cout << "Queue rear is " << q.back() << endl;
	q.push(3);
	cout << "Queue front is " << q.front() << endl;
	cout << "Queue rear is " << q.back() << endl;
	q.push(4);
	cout << "Queue front is " << q.front() << endl;
	cout << "Queue rear is " << q.back() << endl;

	system("pause");
}