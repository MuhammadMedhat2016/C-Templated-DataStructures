#include "Map.h"

template<typename Key, typename Value>
Map<Key, Value>::Map()
{
	tree = nullptr;
}

template<typename Key, typename Value>
Map<Key, Value>::Map(initializer_list<pair<Key, Value>> list)
{
	tree = new AVLTree<pair<Key,Value>>();
	for (auto ele : list)
		this->tree->insert(ele);
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](Key key)
{
	pair<Key, Value> p;
	p.first == key;
	std::cout << this->tree->search(p) << std::endl;
	int *x = new int(1);
	return *x;
}
