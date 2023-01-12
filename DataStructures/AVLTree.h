#pragma once

#include <initializer_list>

using std::initializer_list;

template<typename T>
class BinaryTreeNode;

template<typename T>
class BinaryTree;

template<typename T>
class BST;

template<typename T>
class List;

template<typename T>
class Array;

template<typename T, typename U>
struct MapPair;


template<typename T>
class AVLTreeNode : public BinaryTreeNode<T>
{
public:
	short int bFactor;
	AVLTreeNode();
	AVLTreeNode(T data);
};




template<typename T>
class AVLTree : public BST<T>
{
private:
	// actionPosition is the parent node to newly inserted node or physically deleted node
	BinaryTreeNode<T>* actionPosition;
	void balance();
	BinaryTreeNode<T>* build(BinaryTreeNode<T>* node);
	BinaryTreeNode<T>* Remove(BinaryTreeNode<T>* node, const T& key);
	void relink(AVLTreeNode<T>* p, BinaryTreeNode<T>* parentNode);
public:
	AVLTree();
	AVLTree(initializer_list<T> list);
	AVLTree(const Array<T>& arr);
	AVLTree(const List<T>& list);
	AVLTree(const AVLTree<T>& temp_tree);
	AVLTree(AVLTree<T>&& temp_tree) noexcept;
	void treeBalance() = delete;
	int B_factor() = delete;
	void insert(T data) override;
	void remove(const T& data) override;
	AVLTree<T>& operator = (const AVLTree<T>& tree);
	AVLTree<T>& operator = (AVLTree<T>&& tree) noexcept;
	BinaryTreeNode<T>* getRoot() const;

	~AVLTree();
};

