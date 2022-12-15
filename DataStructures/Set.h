#pragma once

#include <initializer_list>
#include<iostream>
#include <stack>
using std::pair;
using std::stack;
using std::initializer_list;

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3
#define LEVELORDER 4

template<typename T>
class BinaryTreeNode;

template<typename T>
class Array;

template<typename T>
class AVLTree;

template<typename Set>
class SetIterator
{
public:

	using ValueType = typename Set::ValueType;
	using Pointer = typename ValueType*;
	using Reference =  typename ValueType&;
	using const_reference = typename const ValueType&;
	using const_pointer = typename const ValueType*;
	using TreeNode = typename BinaryTreeNode<ValueType>;
	using TreeNodePointer = typename TreeNode*;
	using TreeNodeReference = typename TreeNode&;

	SetIterator(TreeNodePointer);
	// prefix operator ++;
	SetIterator<Set>& operator ++ ();
	// postfix operator ++;
	SetIterator<Set> operator ++ (int);
	// prefix operator --
	SetIterator<Set>& operator -- ();
	// postfix operator --
	SetIterator<Set> operator -- (int);

	const_reference  operator * () const;
	const_pointer  operator -> () const;

	bool operator == (const SetIterator<Set>&);
	bool operator != (const SetIterator<Set>&);


private:
	TreeNodePointer getNextElement();
	void rollBack();
	stack<pair<TreeNodePointer, bool>>* st1;
	stack<TreeNodePointer>* st2;
	TreeNodePointer currentElement;
	TreeNodePointer root;
	int stackPointer;
};

template<typename T>
class Set 
{
private:
	AVLTree<T>* tree;
public:

	using ValueType = T;
	using Iterator = SetIterator<Set<T>>;
	Set();
	Set(initializer_list<T> list);
	Set(Set<T>&);
	Set(Set<T>&&) noexcept;
	void insert(const T&);
	void remove(const T&);
	void clear();
	bool empty();
	bool contains(const T&);
	void erase(const T&);
	void erase(Iterator&);
	Set<T>& operator = (const Set<T>&);
	Set<T>& operator = (Set<T>&&) noexcept;
	Iterator begin();
	Iterator end();
	~Set();

};