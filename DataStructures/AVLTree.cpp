#include "AVLTree.h"
#include <string>
#include <iostream>


#define INORDER 1
#define PREORDER 2
#define POSTORDER 3
#define LEVELORDER 4

template<typename T>
AVLTreeNode<T>::AVLTreeNode()
	:BinaryTreeNode<T>()
{
	this->bFactor = 0;
}

template<typename T>
AVLTreeNode<T>::AVLTreeNode(T data)
	:BinaryTreeNode<T>(data)
{
	this->bFactor = 0;
}

template<typename T>
AVLTree<T>::AVLTree()
	:BST<T>()
{}

template<typename T>
AVLTree<T>::AVLTree(initializer_list<T> list)
	: BST<T>()
{
	for (auto element : list)
		this->insert(element);
}

template<typename T>
AVLTree<T>::AVLTree(const Array<T>& arr)
	: BST<T>()
{
	for (auto element : arr)
		this->insert(element);
}

template<typename T>
AVLTree<T>::AVLTree(const List<T>& list)
	: BST<T>()
{
	for (auto element : list)
		this->insert(element);
}
template<typename T>
AVLTree<T>::AVLTree(const AVLTree<T>& tempTree)
	: BST<T>()
{
	if(tempTree.root)
		this->root = build(tempTree.root);
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::build(BinaryTreeNode<T>* node)
{
	// new AVLTree building in o(n)
	if (node->lchild == node->rchild && node->lchild == nullptr)
		return new AVLTreeNode<T>(node->data);

	BinaryTreeNode<T>* temp = new AVLTreeNode(node->data);
	temp->lchild = build(node->lchild);
	temp->rchild = build(node->rchild);
	return temp;
}

template<typename T>
AVLTree<T>::AVLTree(AVLTree<T>&& tempTree) noexcept
	: BST<T>()
{
	this->root = tempTree.root;
	this->NodesCount = tempTree.NodesCount;
	tempTree.root = nullptr;
	tempTree.NodesCount = 0;
}

template<typename T>
void AVLTree<T>::insert(T data)
{
	BinaryTreeNode<T>* actionPosition = nullptr;
	if (this->root == nullptr)
	{
		this->root = new AVLTreeNode<T>(data);
		this->NodesCount++;
		return;
	}
	BinaryTreeNode<T>* temp = this->root, * q = nullptr;
	while (temp)
	{
		q = temp;
		if (temp->data == data)
			return;
		else if (temp->data > data)
			temp = temp->lchild;
		else
			temp = temp->rchild;
	}
	temp = new AVLTreeNode<T>(data);
	if (q->data > data)
		q->lchild = temp;
	else
		q->rchild = temp;
	this->NodesCount++;
	// actionPosition node is the parent node for newly inserted node
	this->actionPosition = dynamic_cast<AVLTreeNode<T>*>(q);
	// O(logn)^2
	balance();
}

template<typename T>
void AVLTree<T>::balance()
{
	List<BinaryTreeNode<T>*> ancestors;
	// returns all ancestor of the given node except the given node itself so we will add actionPosition in the next step as ancestor node
	this->getAncestors(this->root, this->actionPosition->data, ancestors);
	// add actionPosition node to ancestors
	ancestors.append(this->actionPosition);
	ancestors.reverse();
	AVLTreeNode<T>* parentNode = nullptr, *p = nullptr;

	for (auto element : ancestors)
	{
		p = dynamic_cast<AVLTreeNode<T>*>(element);
		p->bFactor = this->calcHeight(p->lchild) - this->calcHeight(p->rchild);
		if (p->bFactor == 2 || p->bFactor == -2)
		{
			BinaryTreeNode<T>* parentNode = getParent(this->root, p->data);
			relink(p, parentNode);
		}
	}
}

template<typename T>
void AVLTree<T>::relink(AVLTreeNode<T>* p, BinaryTreeNode<T>* parentNode)
{
	AVLTreeNode<T>* q = nullptr, * r = nullptr;
	std::string directions = "";
	if (p->bFactor == 2)
	{
		directions += "L";
		q = dynamic_cast<AVLTreeNode<T>*>(p->lchild);
	}
	else
	{
		directions += "R";
		q = dynamic_cast<AVLTreeNode<T>*>(p->rchild);
	}
	q->bFactor = this->calcHeight(q->lchild) - this->calcHeight(q->rchild);
	// THIS HERE FOR DELETION PURPOSES ONLY -> checking for ZERO // if it's zero we perform the LL rotation if it is not just leave the value as it is
	q->bFactor = q->bFactor == 0 ? 1 : q->bFactor;
	if (q->bFactor == 1)
	{
		directions += "L";
		r = dynamic_cast<AVLTreeNode<T>*>(q->lchild);
	}
	else if (q->bFactor == -1)
	{
		directions += "R";
		r = dynamic_cast<AVLTreeNode<T>*>(q->rchild);
	}
	// till this point we have determined the direction for which the tree should be rotated if it's LL, RR, LR, RL
	// based on the directions we are going to rotate
	if (directions == "LL")
	{
		p->lchild = q->rchild;
		q->rchild = p;
		// check if there is a parent node for these 3 nodes or not
		// if it is there, then conncent it to new root for this subtree which is q
		if (parentNode)
		{
			if (parentNode->lchild == p)
				parentNode->lchild = q;
			else
				parentNode->rchild = q;
		}
		// if there is no parentNode then we should modify the root to point to new root that will achieve balance
		else
			this->root = q;
	}
	else if (directions == "RR")
	{
		p->rchild = q->lchild;
		q->lchild = p;
		// check if there is a parent node for these 3 nodes or not
		// if it is there, then conncent it to new root for this subtree which is q
		if (parentNode)
		{
			if (parentNode->lchild == p)
				parentNode->lchild = q;
			else
				parentNode->rchild = q;
		}
		// if there is no parentNode then we should modify the root to point to new root that will achieve balance
		else
		{
			this->root = q;
		}

	}
	else if (directions == "LR")
	{
		p->lchild = r->rchild;
		q->rchild = r->lchild;
		r->lchild = q;
		r->rchild = p;

		if (parentNode)
		{
			if (parentNode->lchild == p)
				parentNode->lchild = r;
			else
				parentNode->rchild = r;
		}
		// if there is no parentNode then we should modify the root to point to new root that will achieve balance
		else
			this->root = r;
	}
	else if (directions == "RL")
	{
		p->rchild = r->lchild;
		q->lchild = r->rchild;
		r->lchild = p;
		r->rchild = q;

		if (parentNode)
		{
			if (parentNode->lchild == p)
				parentNode->lchild = r;
			else
				parentNode->rchild = r;
		}
		// if there is no parentNode then we should modify the root to point to new root that will achieve balance
		else
			this->root = r;
	}

}
template<typename T>
void AVLTree<T>::remove(const T& key)
{
	bool bol = this->search(key);
	if (bol)
		this->NodesCount--;
	// actionPosition is the parent node of physically deleted node
	this->root = Remove(this->root, key);
	// if there is at least one node go balance 
	if(this->root)
		balance();
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::Remove(BinaryTreeNode<T>* node, const T& key)
{
	// if node is not valid
	if (!node)
		return nullptr;

	// first searching for the key node element 
	if (node->data > key)
	{
		node->lchild = Remove(node->lchild, key);
	}
	else if (node->data < key)
	{
		node->rchild = Remove(node->rchild, key);
	}
	else if (node->data == key) // found the element prepare for removing
	{

		// if it is a leaf node remove it at once
		if (node->lchild == node->rchild && node->lchild == nullptr)
		{
			this->actionPosition = getParent(this->root, node->data);
			delete node;
			return nullptr;
		}
		// if it has one child node -> connect it's parent to it's only child then remove the node
		else if ((node->lchild && !node->rchild) || (!node->lchild && node->rchild))
		{
			this->actionPosition = getParent(this->root, node->data);
			BinaryTreeNode<T>* temp;
			if (node->lchild)
				temp = node->lchild;
			else
				temp = node->rchild;

			delete node;
			return temp;
		}
		// if it has 2 children -> replace it with it's min ele of right sub-tree or max ele of left sub-tree depending on the height of left and right subtree
		else
		{
			int leftHeight = this->calcHeight(node->lchild);
			int rightHeight = this->calcHeight(node->rchild);
			// if height of left sub-tree is grater then find the max of left sub-tree
			if (leftHeight > rightHeight)
			{
				BinaryTreeNode<T>* mx = this->Max(node->lchild);
				T temp = mx->data;
				node->lchild = Remove(node->lchild, mx->data);
				node->data = temp;
			}
			// if height of right sub-tree is grater then find the min of right sub-tree
			else
			{
				BinaryTreeNode<T>* mn = this->Min(node->rchild);
				T temp = mn->data;
				node->rchild = Remove(node->rchild, mn->data);
				node->data = temp;
			}
		}
	}
	return node;
}



template<typename T>
AVLTree<T>& AVLTree<T>::operator = (const AVLTree<T>& tree)
{
	std::cout << "inside cpy assinment operator " << std::endl;
	this->~AVLTree();
	this->root = build(tree.root);
	return *this;
}

template<typename T>
AVLTree<T>& AVLTree<T>::operator = ( AVLTree<T>&& tree) noexcept
{
	std::cout << "inside move assinment operator " << std::endl;
	this->~AVLTree();

	this->root = tree.root;
	this->NodesCount = tree.NodesCount;
	this->actionPosition = tree.actionPosition;

	tree.root = nullptr;
	tree.actionPosition = nullptr;
	tree.NodesCount = -1;

	return *this;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::getRoot() const
{
	return this->root;
}


template<typename T>
AVLTree<T>::~AVLTree()
{
	// by befault calls the destructor of parent class 
}