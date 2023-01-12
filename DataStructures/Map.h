#pragma once

#include<initializer_list>
#include <utility>
#include <iostream>
#include <stack>

using std::initializer_list;

template<typename T>
class AVLTree;

template<typename T>
class BinaryTreeNode;


template<typename T>
class Array;

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3
#define LEVELORDER 4

template<typename T, typename U>
struct MapPair
{
	T first;
	U second;
	bool operator < (const MapPair<T,U>& mp);
	bool operator > (const MapPair<T,U>& mp);
	bool operator <= (const MapPair<T,U>& mp);
	bool operator >= (const MapPair<T,U>& mp);
	bool operator == (const MapPair<T,U>& mp);
	MapPair<T,U>& operator = (const MapPair<T,U>& mp);
};

template<typename MAP>
class MapIterator
{
public:
	using KeyType = typename MAP::KeyValueType;
	using ValueType = typename MAP::ValueType;
	using MPair = MapPair<KeyType, ValueType>;
	using TreeNode = BinaryTreeNode<MapPair<KeyType, ValueType>>;
	using TreeNodePointer = TreeNode*;
	using TreeNodeReference = TreeNode&;
	
	MapIterator(const MapIterator<MAP>& itr);
	MapIterator(TreeNodePointer);

	MapIterator<MAP> operator++(int);
	MapIterator<MAP>& operator++();

	MapIterator<MAP> operator --(int);
	MapIterator<MAP>& operator --();

	MPair& operator *();
	MPair* operator ->();

	bool operator != (const MapIterator<MAP>&);

private:
	TreeNodePointer getNextElement();
	void rollback();
	TreeNodePointer root;
	std::stack<std::pair<TreeNodePointer, bool>>* st1;
	TreeNodePointer currentElement;
	std::stack<TreeNodePointer>* st2;
	int stackPointer;

};




template<typename Key, typename Value>
class Map
{
private:
	AVLTree<MapPair<Key, Value>> *tree;
public:
	
	using KeyValueType = Key;
	using ValueType = Value;
	using Iterator = MapIterator<Map>;

	Map();
	Map(const initializer_list<MapPair<Key, Value>>& list);
	Map(const Map<Key, Value>& map);
	Map(Map<Key, Value>&& map);
	Value& operator [] (const Key& key);
	void insert(const MapPair<Key, Value>& mp);
	void clear();
	void erase(const Key& key);
	Array<Key> getKeys() const;
	Array<Value> getValues() const;

	Iterator begin();
	Iterator end();
};

