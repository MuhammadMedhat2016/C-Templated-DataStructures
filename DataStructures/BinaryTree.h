#pragma once
#include <iostream>

template<class T>
class Array;


template<typename T>
class BinaryTreeNode
{
public:
	BinaryTreeNode* lchild;
	T data;
	BinaryTreeNode* rchild;
	BinaryTreeNode();
	BinaryTreeNode(T data);
	// for AVLTreeNode class to be dowcasted
	virtual void dummy();
};

#define INORDER 1
#define PREORDER 2
#define POSTORDER 3
#define LEVELORDER 4

template<typename T>
class BinaryTree
{
private:
	void InOrder(BinaryTreeNode<T>* root, Array<T>& ret) const;
	void PreOrder(BinaryTreeNode<T>* root, Array<T>& ret) const;
	void PostOrder(BinaryTreeNode<T>* root, Array<T>& ret) const;
	void LevelOrder(BinaryTreeNode<T>* root, Array<T>& ret) const;
	int calcNumOfDeg2Nodes(BinaryTreeNode<T>* root) const;
	int calcNumOfDeg1Nodes(BinaryTreeNode<T>* root) const;
	void deleteTree(BinaryTreeNode<T>* root);
	void createBinaryTree();
protected:
	BinaryTreeNode<T>* root;
	int NodesCount;
	int calcHeight(BinaryTreeNode<T>* root) const;
public:
	BinaryTree();
	virtual void insert(T data) = 0;
	virtual bool search(const T& data) = 0;
	virtual int getTreeHeight() const final;
	virtual Array<T> traverse(const int traverseType) const final;
	virtual int getNumOfDeg2Nodes() const final;
	virtual int getNumOfDeg1Nodes() const final;
	virtual int getNumOfLeafNodes() const final;
	virtual bool is_strict() const final;
	virtual bool is_full() const final;
	virtual bool is_complete() const final;
	virtual int getNodesCount() const final;
	~BinaryTree();

};
