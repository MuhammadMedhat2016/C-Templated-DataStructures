#include <iostream>
#include "DataStructures.h"
#include <map>
#include<utility>
using namespace std;
int main()
{
	Map<int, int> mp = { {1,2}, {3,4} };
	mp.insert({ 5,4 });

	Map<int, int>::Iterator it = mp.begin();
	
	for (; it != mp.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}

	--it;
	cout << it->first << endl;
	it--;
	cout << it->first << endl;
	it--;
	cout << it->first << endl;



	return 0;
}