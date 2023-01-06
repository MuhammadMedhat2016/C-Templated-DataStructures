#include "RBT.h"



template<typename T>
RBTNode<T>::RBTNode(T data, color c)
	: BinaryTreeNode<T>(data)
{
	this->c = c;
}

template<typename T>
RBT<T>::RBT()
	:BST<T>()
{
}

template<typename T>
RBT<T>::RBT(initializer_list<T> list)
	:BST<T>()
{
	for (auto element : list)
		this->insert(element);
}

template<typename T>
RBT<T>::RBT(const Array<T>& arr)
	: BST<T>()
{
	for (auto element : arr)
		this->insert(element);
}

template<typename T>
RBT<T>::RBT(const List<T>& list)
	:BST<T>()
{
	for (auto element : list)
		this->insert(element);
}

template<typename T>
RBT<T>::RBT(const RBT<T>& temp)
	:BST<T>()
{
	this->root = build(dynamic_cast<RBTNode<T>*>(temp->root));
}

template<typename T>
BinaryTreeNode<T>* RBT<T>::build(const RBTNode<T>* node)
{
	if (!node)
		return nullptr;
	BinaryTreeNode<T>* newNode = new RBTNode<T>(node->data, node->c);
	newNode->left = build(node->lchild);
	newNode->rchild = build(node->rchild);

	return newNode;
}

template<typename T>
RBT<T>::RBT(RBT<T>&& temp) noexcept
{
	this->root = temp.root;
	this->NodesCount = temp.NodesCount;

	temp.root = nullptr;
	temp.NodesCount = -1;
}

template <typename T>
void RBT<T>::insert(T value)
{
	if (!this->root)
	{
		this->root = new RBTNode<T>(value, BLACK);
		this->NodesCount++;
		return;
	}
	BinaryTreeNode<T> *p = nullptr, *temp = this->root;
	while (temp)
	{
		p = temp;
		if (temp->data == value)
			return;
		else if (temp->data > value)
			temp = temp->lchild;
		else
			temp = temp->rchild;
	}
	temp = new RBTNode<T>(value, RED);
	if (p->data > value)
		p->lchild = temp;
	else
		p->rchild = temp;
	this->NodesCount++;
	insertFix(dynamic_cast<RBTNode<T>*>(temp));
}

template<typename T>
int RBT<T>::balckDepth(RBTNode<T>* node)
{
	if (!node)
		return 0;
	int left = this->balckDepth(node->lchild);
	int right = this->balckDepth(node->rchild);
	int ret = std::max(left, right);
	return ret + node->c == BLACK ? 1 : 0;
}

template<typename T>
RBTNode<T>* RBT<T>::cast(BinaryTreeNode<T>* ptr)
{
	return dynamic_cast<RBTNode<T>*>(ptr);
}


template<typename T>
void RBT<T>::insertFix(RBTNode<T>* node)
{
	RBTNode<T>* parent = cast(this->getParent(this->root, node->data));
	// if parent color is black it's okay then return
	if (parent->c == BLACK)
		return;
	RBTNode<T>* RBTroot = cast(this->root);;
	RBTNode<T>* grandParent = cast(this->getParent(this->root, parent->data));
	RBTNode<T>* uncle = cast(grandParent->lchild) == parent ? cast(grandParent->rchild) : cast(grandParent->lchild);
	// if the uncle exists and its color is red
	if (uncle && uncle->c == RED)
	{
		parent->c = uncle->c = BLACK;
		// if the grandparent is not the root of the tree GO recusivly FIX if it's the root then DO NOT DO ANYTHING
		if (grandParent != RBTroot)
		{
			grandParent->c = RED;
			insertFix(grandParent);
		}
		return;
	}
	// if the uncle is BLACK or does not exist (namely NIL)
	// ROTATION AND RECOLOR
	std::string directions = "";
	// determining rotation directions
	directions += cast(grandParent->lchild) == parent ? "L" : "R";
	directions += cast(parent->lchild) == node ? "L" : "R";
	
	RBTNode<T>* growthParent = cast(this->getParent(this->root, grandParent->data));

	if (directions == "LL")
	{ 
		grandParent->lchild = parent->rchild;
		parent->rchild = grandParent;

		if (growthParent)
		{
			if (growthParent->lchild == grandParent)
				growthParent->lchild = parent;
			else
				growthParent->rchild = parent;
		}
		else
			this->root = parent;
		
		parent->c = BLACK;
		grandParent->c = RED;
	}
	else if (directions == "RR")
	{
		grandParent->rchild = parent->lchild;
		parent->lchild = grandParent;

 		if (growthParent)
		{
			if (growthParent->lchild == grandParent)
				growthParent->lchild = parent;
			else
				growthParent->rchild = parent;
		}
		else
			this->root = parent;

		parent->c = BLACK;
		grandParent->c = RED;
	}
	else if (directions == "LR")
	{
		parent->rchild = node->lchild;
		grandParent->lchild = node->rchild;
		node->lchild = parent;
		node->rchild = grandParent;

		if (growthParent)
		{
			if (growthParent->lchild == grandParent)
				growthParent->lchild = node;
			else
				growthParent->rchild = node;
		}
		else
			this->root = node;
		node->c = BLACK;
		grandParent->c = RED;
	}
	else if (directions == "RL")
	{
		parent->lchild = node->rchild;
		grandParent->rchild = node->lchild;
		node->rchild = parent;
		node->lchild = grandParent;

		if (growthParent)
		{
			if (growthParent->lchild == grandParent)
				growthParent->lchild = node;
			else
				growthParent->rchild = node;
		}
		else
			this->root = node;
		node->c = BLACK;
		grandParent->c = RED;
	}
}

template<typename T>
void RBT<T>::printColors(RBTNode<T> *node)
{
	if (!node)
		return;
	printColors(cast(node->lchild));
	std::cout <<node->data <<" " << node->c << "\n";
	printColors(cast(node->rchild));
}

template<typename T>
void RBT<T>::print()
{
	printColors(cast(this->root));
}