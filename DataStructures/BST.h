#pragma once

#include <initializer_list>

using std::initializer_list;


template<typename T>
class Array;

template<typename T>
class List;

template<typename T>
class BinaryTreeNode;

template<typename T>
class BinaryTree;

template<typename T>
class BST : public BinaryTree<T>
{
private:
	BinaryTreeNode<T>* Search(BinaryTreeNode<T>* root, const T& data);
	void getTreeNodesAddresses(BinaryTreeNode<T> *node, Array<BinaryTreeNode<T>*>& addresses);
	BinaryTreeNode<T>* createBalancedTree(int q, int r, Array<BinaryTreeNode<T>*>& addresses);
	BinaryTreeNode<T>* Remove(BinaryTreeNode<T>* root, const T& key);

protected:
	BinaryTreeNode<T>* Min(BinaryTreeNode<T>* root) const;
	BinaryTreeNode<T>* Max(BinaryTreeNode<T>* root) const;
	void getAncestors(BinaryTreeNode<T>* root, const T& data, List<BinaryTreeNode<T>*>& ancestors);
	BinaryTreeNode<T>* inorderSuccessor(const T& data);
	BinaryTreeNode<T>* inorderPredecessor(const T& data);
public:
	BST();
	BST(initializer_list<T> list);
	virtual void insert(T data) override;
	bool search(const T& data) override final;
	T min() const;
	T max() const;
	virtual void remove(const T& key);
	void treeBalance();
	int B_factor();
	
};