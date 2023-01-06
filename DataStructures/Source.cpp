#include <iostream>
#include "DataStructures.h"
using namespace std;

int main()
{
	RBT<int> r = {10,18,7,15,16,30,25,40,60,2,1,70};
	Array<int> in = r.traverse(INORDER);
	Array<int> pre = r.traverse(PREORDER);

	for (int ele : in)
		cout << ele << " ";
	cout << endl;

	for (int ele : pre)
		cout << ele << " ";
	cout << endl;

	r.print();


	return 0;
}