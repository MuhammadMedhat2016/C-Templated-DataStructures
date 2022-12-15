#include <iostream>
#include "DataStructures.h"
using namespace std;

int main()
{
	Heap<int, Greater<int>> h = { 5,19,12,15,20,9,10,3 };
	h.showHeap();
	Array<int> arr = h.HeapSort();
	for (int ele : arr)
		cout << ele << " ";
	cout << "Hello World" << endl;

	return 0;
}