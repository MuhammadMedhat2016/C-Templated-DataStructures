#include "Map.h"


template<typename T, typename U>
bool MapPair<T, U>::operator<(const MapPair<T,U>& mp)
{
	return this->first < mp.first;
}

template<typename T, typename U>
bool MapPair<T, U>::operator>(const MapPair<T,U>& mp)
{
	return this->first > mp.first;
}

template<typename T, typename U>
bool MapPair<T, U>::operator<=(const MapPair<T,U>& mp)
{
	return this->first <= mp.first;
}

template<typename T, typename U>
bool MapPair<T, U>::operator>=(const MapPair<T,U>& mp)
{
	return this->first >= mp.first;
}

template<typename T, typename U>
bool MapPair<T, U>::operator==(const MapPair<T,U>& mp)
{
	return this->first == mp.first;
}

template<typename T, typename U>
MapPair<T,U>& MapPair<T, U>::operator = (const MapPair<T,U>& mp)
{
	this->first = mp.first;
	this->second = mp.second;
	return *this;
}

template<typename MAP>
MapIterator<MAP>::MapIterator(MapIterator<MAP>::TreeNodePointer root)
{
	if (root)
	{
		this->root = root;
		this->stackPointer = 0;
		st1 = new std::stack<pair<TreeNodePointer, bool>>();
		st2 = new std::stack<TreeNodePointer>();
		st1->push({ this->root, false });
		this->currentElement = getNextElement();
	}
	else
	{
		this->root = nullptr;
		this->st1 = nullptr;
		this->st2 = nullptr;
		this->currentElement = nullptr;
	}
	
}
template<typename MAP>
MapIterator<MAP>::MapIterator(const MapIterator<MAP>& itr)
{
	this->currentElement = itr.currentElement;
	this->st1 = itr.st1;
	this->st2 = itr.st2;
	this->stackPointer = itr.stackPointer;
	this->root = itr.root;
}
template<typename MAP>
MapIterator<MAP>::TreeNodePointer MapIterator<MAP>::getNextElement()
{
	st2->push(this->currentElement);
	if (st1->empty())
	{
		this->root = nullptr;
		this->currentElement = nullptr;
		return currentElement;
	}
	if (stackPointer)
	{
		std::pair<TreeNodePointer, bool> element = st1->top();
		st1->pop();
		stackPointer--;
		return element.first;
	}
	while (!st1->empty())
	{
		auto [node, bol] = st1->top();
		st1->pop();
		if (!bol)
		{
			while (node)
			{
				st1->push({ node, true });
				node = node->lchild;
			}
			std::pair<TreeNodePointer, bool> element = st1->top();
			st1->pop();
			return element.first;
		}
		else
		{
			if (node->rchild)
				st1->push({ node->rchild, false });
			return node;
		}
	}
}
template<typename MAP>
void MapIterator<MAP>::rollback()
{
	if (st2->empty())
		throw new std::out_of_range("there are no elements to rollback to it");
	st1->push({ this->currentElement , true });
	this->stackPointer++;
	this->currentElement = st2->top();
	st2->pop();
}

template<typename MAP>
MapIterator<MAP> MapIterator<MAP>::operator++(int)
{
	MapIterator<MAP> temp = *this;
	this->currentElement = this->getNextElement();
	return temp;
}

template<typename MAP>
MapIterator<MAP>& MapIterator<MAP>::operator++()
{
	this->currentElement = this->getNextElement();
	return *this;
}

template<typename MAP>
MapIterator<MAP> MapIterator<MAP>::operator--(int)
{
	MapIterator<MAP> temp = *this;
	this->rollback();
	return temp;
}

template<typename MAP>
MapIterator<MAP>& MapIterator<MAP>::operator--()
{
	this->rollback();
	return *this;
}

template<typename MAP>
bool MapIterator<MAP>::operator!=(const MapIterator& itr)
{
	return this->currentElement != itr.currentElement;
}

template<typename MAP>
MapIterator<MAP>::MPair& MapIterator<MAP>::operator * ()
{
	return (this->currentElement->data);
}

template<typename MAP>
MapIterator<MAP>::MPair* MapIterator<MAP>::operator -> ()
{
	return &(this->currentElement->data);
}


template<typename Key, typename Value>
Map<Key, Value>::Map()
{
	tree = new AVLTree<MapPair<Key,Value>>();
}

template<typename Key, typename Value>
Map<Key, Value>::Map(const initializer_list<MapPair<Key,Value>>& list)
{
	tree = new AVLTree<MapPair<Key,Value>>();
	for (auto ele : list)
		this->tree->insert(ele);
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{
	MapPair<Key, Value> p = { key };
	BinaryTreeNode<MapPair<Key,Value>> *node = this->tree->Search(this->tree->getRoot(), p);
	if (node == nullptr)
		this->tree->insert({ key,Value() });
	else
		return node->data.second;
	
	node = this->tree->Search(this->tree->getRoot(), p);
	return node->data.second;
}

template<typename Key, typename Value>
void Map<Key, Value>::insert(const MapPair<Key, Value>& mp)
{
	this->tree->insert(mp);
}

template<typename Key, typename Value>
void Map<Key, Value>::clear()
{
	delete this->tree;
	tree = new AVLTree<MapPair<Key, Value>>();
}

template<typename Key, typename Value>
void Map<Key, Value>::erase(const Key& key)
{
	MapPair<Key, Value> p = { key };
	this->tree->remove(p);
}

template<typename Key,typename Value>
Array<Key> Map<Key,Value>::getKeys() const
{
	Array<MapPair<Key,Value>> temp = this->tree->traverse(INORDER);
	Array<Key> ret;
	for (auto [key, value] : temp)
		ret.append(key);
	return ret;
}

template<typename Key, typename Value>
Array<Value> Map<Key, Value>::getValues() const
{
	Array<MapPair<Key, Value>> temp = this->tree->traverse(INORDER);
	Array<Key> ret;
	for (auto [key, value] : temp)
		ret.append(value);
	return ret;
}

template<typename Key, typename Value>
Map<Key, Value>::Iterator Map<Key, Value>::begin()
{
	return Iterator(this->tree->getRoot());
}

template<typename Key, typename Value>
Map<Key, Value>::Iterator Map<Key, Value>::end()
{
	return Iterator(nullptr);
}