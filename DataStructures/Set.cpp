#include "Set.h"
#include <stdexcept>

template<typename Set>
SetIterator<Set>::SetIterator(SetIterator<Set>::TreeNodePointer root)
	:root(root)
{
	if (root)
	{
		st1 = new stack<pair<TreeNodePointer, bool>>();
		st2 = new stack<TreeNodePointer>();
		st1->push({ root , 0 });
		currentElement = getNextElement();
		stackPointer = 0;
	}
	else
	{
		st1 = nullptr;
		st2 = nullptr;
		currentElement = nullptr;
	}
}

template<typename T>
SetIterator<T>::TreeNodePointer SetIterator<T>::getNextElement()
{
	// if stack is empty then there is no node to traverse => clean up the memory
	if (st1->empty())
	{
		delete st1;
		delete st2;
		currentElement = nullptr;
		return currentElement;
	}
	// if there are rolled back values
	if (stackPointer)
	{
		pair<TreeNodePointer, bool> temp = st1->top();
		TreeNodePointer element = temp.first;
		st1->pop();
		stackPointer--;
		return element;
	}
	// find the next element in inorder traversal
	while (!st1->empty())
	{
		pair<TreeNodePointer, bool> temp = st1->top();
		TreeNodePointer ptr = temp.first;
		if (temp.second == 0)
		{
			st1->pop();
			st1->push({ temp.first, 1 });
			while (ptr->lchild)
			{
				ptr = ptr->lchild;
				st1->push({ ptr, 1 });
			}
			ptr = st1->top().first;
			st1->pop();
		}
		else
		{
			st1->pop();
		}
		if (ptr->rchild)
			st1->push({ ptr->rchild, 0 });
		return ptr;
	}
}
template<typename T>
void SetIterator<T>::rollBack()
{
	if (st2->empty())
		throw new std::out_of_range("there are no elements to rollback to it");
	TreeNodePointer element = st2->top();
	st2->pop();
	st1->push({ currentElement, 1 });
	currentElement = element;
	stackPointer++;
}
// postfix ++ operator
template<typename T> 
SetIterator<T> SetIterator<T>::operator++(int)
{
	st2->push(currentElement);
	SetIterator<T> temp = *this;
	currentElement = this->getNextElement();
	return temp;
}
//prefix ++ operator
template<typename T>
SetIterator<T>& SetIterator<T>::operator++()
{
	st2->push(currentElement);
	currentElement = this->getNextElement();
	return *this;
}

// postfix -- operator
template<typename T>
SetIterator<T> SetIterator<T>::operator--(int)
{

	SetIterator<T> temp = *this;
	this->rollBack();
	return temp;
}

//prefix -- operator
template<typename T>
SetIterator<T>& SetIterator<T>::operator--()
{
	this->rollBack();
	return *this;
}

template<typename T>
bool SetIterator<T>::operator == (const SetIterator<T>& iterator)
{
	return this->currentElement == iterator.currentElement;
}

template<typename T>
bool SetIterator<T>::operator != (const SetIterator<T>& iterator)
{
	return this->currentElement != iterator.currentElement;
}

template<typename T>
SetIterator<T>::const_reference SetIterator<T>::operator *() const
{
	return currentElement->data;
}

template<typename T>
SetIterator<T>::const_pointer SetIterator<T>::operator -> () const
{
	return currentElement;
}

template<typename T>
Set<T>::Set()
{
	this->tree = new AVLTree<T>();
}

template<typename T>
Set<T>::Set(initializer_list<T> list)
{
	this->tree = new AVLTree<T>();

	for (auto element : list)
		this->tree->insert(element);
}

template<typename T>
Set<T>::Set(Set<T>& set)
{
	this->tree = new AVLTree<T>(*set.tree);
}

template<typename T>
Set<T>::Set(Set<T>&& set) noexcept
{
	this->tree = new AVLTree<T>(std::move(*set.tree));
	set.tree = nullptr;
}

template<typename T>
void Set<T>::insert(const T& data)
{
	this->tree->insert(data);
}

template<typename T>
void Set<T>::remove(const T& data)
{
	this->tree->remove(data);
}

template<typename T>
void Set<T>::clear()
{
	delete this->tree;
	this->tree = new AVLTree<T>();
}

template<typename T>
Set<T>::~Set()
{
	delete this->tree;
}

template<typename T>
bool Set<T>::empty()
{
	return this->tree->getNodesCount() == 0 ? 1 : 0;
}

template<typename T>
Set<T>& Set<T>::operator = (const Set<T>& set)
{
	*this->tree = *set.tree;
	return *this;
}

template<typename T>
Set<T>& Set<T>::operator = (Set<T>&& set) noexcept
{
	*this->tree = std::move(*set.tree);
	set.tree = nullptr;
	return *this;
}

template<typename T>
Set<T>::Iterator Set<T>::begin()
{
	return Iterator(this->tree->getRoot());
}

template<typename T>
Set<T>::Iterator Set<T>::end()
{
	return Iterator(nullptr);
}

template<typename T>
bool Set<T>::contains(const T& data)
{
	return this->tree->search(data);
}

template<typename T>
void Set<T>::erase(const T& data)
{
	this->tree->remove(data);
}

template<typename T>
void Set<T>::erase(Set<T>::Iterator& it)
{
	this->tree->remove(*it);
}












