#pragma once

#include<initializer_list>
#include <utility>
#include <iostream>
using std::initializer_list;
using std::pair;

template<typename T>
class AVLTree;


template<typename Key, typename Value>
class Map
{
private:
	AVLTree<pair<Key, Value>> *tree;
public:
	Map();
	Map(initializer_list<pair<Key, Value>>);
	Map(const Map<Key, Value>& map);
	Map(Map<Key, Value>&& map);
	Value& operator [] (Key key);







};

