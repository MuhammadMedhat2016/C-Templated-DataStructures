#include "BST.h"

template<typename T>
BST<T>::BST()
	:BinaryTree<T>()
{}


template<typename T>
BST<T>::BST(initializer_list<T> list)
	: BinaryTree<T>()
{
	for (auto element : list)
		this->insert(element);
}


template<typename T>
bool BST<T>::search(const T& data)
{
	return Search(this->root, data) == nullptr ? false : true;
}


template<typename T>
BinaryTreeNode<T>* BST<T>::Search(BinaryTreeNode<T>* node, const T& data)
{
	if (!node)
		return nullptr;
	if (node->data == data)
		return node;
	else if (node->data > data)
		return Search(node->lchild, data);
	else
		return Search(node->rchild, data);
}

template<typename T>
void BST<T>::insert(T data)
{
	if (this->root == nullptr)
	{
		this->root = new BinaryTreeNode<T>(data);
		this->NodesCount++;
		return;
	}
	BinaryTreeNode<T> *temp = this->root, *q = nullptr;
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
	temp = new BinaryTreeNode<T>(data);
	if (q->data > data)
		q->lchild = temp;
	else
		q->rchild = temp;
	this->NodesCount++;
}

template<typename T>
T BST<T>::min() const
{
	return Min(this->root)->data;
}

template<typename T>

BinaryTreeNode<T>* BST<T>::Min(BinaryTreeNode<T>* node) const
{
	if (!node->lchild)
		return node;
	return Min(node->lchild);
}

template<typename T>
T BST<T>::max() const
{
	return Max(this->root)->data;
}

template<typename T>
BinaryTreeNode<T>* BST<T>::Max(BinaryTreeNode<T>* node) const
{
	if (!node->rchild)
		return node;
	return Max(node->rchild);
}

template<typename T>
void BST<T>::remove(const T& key)
{
	bool bol = this->search(key);
	if (bol)
		this->NodesCount--;
	Remove(this->root, key);
}

template<typename T>
BinaryTreeNode<T>* BST<T>::Remove(BinaryTreeNode<T>* node, const T& key)
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
			delete node;
			return nullptr;
		}
		// if it has one child node -> connect it's parent to it's only child then remove the node
		else if ((node->lchild && !node->rchild) || (!node->lchild && node->rchild))
		{
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
				node->data = mx->data;
				node->lchild = Remove(node->lchild, node->data);
			}
			// if height of right sub-tree is grater then find the min of right sub-tree
			else
			{
				BinaryTreeNode<T>* mn = this->Min(node->rchild);
				node->data = mn->data;
				node->rchild = Remove(node->rchild, node->data);
			}
		}
	}
	return node;
}

template<typename T>
int BST<T>::B_factor()
{
	return abs(this->calcHeight(this->root->lchild) - this->calcHeight(this->root->rchild));
}

template<typename T>
void BST<T>::getTreeNodesAddresses(BinaryTreeNode<T> *node, Array<BinaryTreeNode<T>*>& addresses)
{
	if (!node)
		return;
	getTreeNodesAddresses(node->lchild, addresses);
	addresses.append(node);
	getTreeNodesAddresses(node->rchild, addresses);
}

template<typename T>
BinaryTreeNode<T>* BST<T>::createBalancedTree(int q, int r, Array<BinaryTreeNode<T>*>& addresses)
{
	if (q > r)
		return nullptr;
	int mid = (q + r) / 2;
	addresses[mid]->lchild = addresses[mid]->rchild = nullptr;
	addresses[mid]->lchild = createBalancedTree(q, mid - 1,addresses);
	addresses[mid]->rchild = createBalancedTree(mid + 1, r, addresses);
	return addresses[mid];
}
template<typename T>
void BST<T>::treeBalance()
{
	Array<BinaryTreeNode<T>*> addresses(this->NodesCount);
	getTreeNodesAddresses(this->root, addresses);
	this->root = createBalancedTree(0, addresses.getLength() - 1, addresses);
}

template<typename T>
BinaryTreeNode<T>* BST<T>::inorderSuccessor(const T& data)
{
	// search to find it first
	BinaryTreeNode<T>* temp = Search(this->root, data);
	// if it is not found
	if (!temp)
		return nullptr;
	// if it has a right subtree find the min of the subtree
	if (temp->rchild)
		return Min(temp->rchild);
	// if it has no right subtree find the fisrt ancestor for which the given node on left subtree
	List<BinaryTreeNode<T>*> ancestors;
	getAncestors(this->root, data, ancestors);
	ancestors.reverse();
	for (auto ancestor : ancestors)
		if (ancestor->data > data)
			return ancestor;
	return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BST<T>::inorderPredecessor(const T& data)
{
	// search to find it first
	BinaryTreeNode<T>* temp = Search(this->root, data);
	// if it is not found
	if (!temp)
		return nullptr;
	// if it has a left subtree find the max of the subtree
	if (temp->lchild)
		return Max(temp->lchild);
	// if it has no left subtree find the ancestor for which the given node on right subtree
	List<BinaryTreeNode<T>*> ancestors;
	getAncestors(this->root, data, ancestors);
	ancestors.reverse();
	for (auto ancestor : ancestors)
		if (ancestor->data < data)
			return ancestor;
	return nullptr;
}


template<typename T>
void BST<T>::getAncestors(BinaryTreeNode<T>* node, const T& data, List<BinaryTreeNode<T>*>& ancestors)
{
	if (!node)
		return;
	if (node->data == data)
		return;
	ancestors.append(node);
	if (node->data > data)
		getAncestors(node->lchild, data, ancestors);
	else if (node->data < data)
		getAncestors(node->rchild, data, ancestors);
}

