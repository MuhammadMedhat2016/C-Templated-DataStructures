#pragma once
#include <initializer_list>
#include <algorithm>
#include <string>
#include <iostream>
using std::initializer_list;


template<typename T>
class BinaryTreeNode;

template<typename T>
class BST;

template<typename T>
class Array;

template<typename T>
class List;

enum color
{
	RED, BLACK
};

template<typename T>
class RBTNode : public BinaryTreeNode<T>
{
public:
	color c;
	RBTNode(T data, color c);
};

template<typename T>
class RBT : public BST<T>
{
private:
	BinaryTreeNode<T>* build(const RBTNode<T>* node);
	int balckDepth(RBTNode<T>* node);
	void insertFix(RBTNode<T> *node);
	RBTNode<T>* cast(BinaryTreeNode<T>* ptr);

public:
	RBT();
	RBT(initializer_list<T> list);
	RBT(const Array<T>& arr);
	RBT(const List<T>& list);
	RBT(const RBT<T>& temp_tree);
	RBT(RBT<T>&& temp_tree) noexcept;
	void treeBalance() = delete;
	int B_factor() = delete;
	void printColors(RBTNode<T>* node);
	void print();
	void insert(T value);
	

};
