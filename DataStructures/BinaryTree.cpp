#include "BinaryTree.h"
#include <queue>

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	lchild = rchild = nullptr;
	data = T();
}

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(T data)
	:data(data)
{
	lchild = rchild = nullptr;
}

template<typename T>
void BinaryTreeNode<T>::dummy()
{
	// this function is for downcasting using dynamic_cast on BinaryTreeNode class to AVLTreeNode class object
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
	NodesCount = 0;
}

template<typename T>
Array<T> BinaryTree<T>::traverse(const int traverseType) const
{

	Array<T> temp = Array<T>(this->NodesCount);

	if (traverseType == INORDER)
	{
		InOrder(root,temp);

	}
	else if (traverseType == PREORDER)
	{
		PreOrder(root,temp);

	}
	else if (traverseType == POSTORDER)
	{
		PostOrder(root,temp);

	}
	else if (traverseType == LEVELORDER)
	{
		LevelOrder(root,temp);
	}
	return temp;
}

template<typename T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* node, Array<T>& ret) const
{
	if (!node)
		return;
	InOrder(node->lchild, ret);
	ret.append(node->data);
	InOrder(node->rchild,ret);
}

template<typename T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* node, Array<T>& ret) const
{
	if (!node)
		return;

	ret.append(node->data);
	PreOrder(node->lchild, ret);
	PreOrder(node->rchild,ret);
}

template<typename T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* node, Array<T>& ret) const
{
	if (!node)
		return;

	PostOrder(node->lchild, ret);
	PostOrder(node->rchild,ret);
	ret.append(node->data);
}

template<typename T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode<T>* node, Array<T>& ret) const
{
	std::queue<BinaryTreeNode<T>*> q;
	q.push(node);
	while (!q.empty())
	{
		node = q.front();
		ret.append(node->data);
		if(node->lchild) q.push(node->lchild);
		if (node->rchild) q.push(node->rchild);
		q.pop();
	
	}
}

template<typename T>
int BinaryTree<T>::getTreeHeight() const
{
	return calcHeight(this->root) - 1;
}

template<typename T>
int BinaryTree<T>::calcHeight(BinaryTreeNode<T>* node) const
{
	if (!node)
		return 0;
	return std::max(calcHeight(node->lchild), calcHeight(node->rchild)) + 1;
}

template<typename T>
int BinaryTree<T>::getNumOfDeg2Nodes() const
{
	return calcNumOfDeg2Nodes(this->root);
}

template<typename T>
int BinaryTree<T>::calcNumOfDeg2Nodes(BinaryTreeNode<T>* node) const
{
	if (!node)
		return 0;
	int temp = calcNumOfDeg2Nodes(node->lchild) + calcNumOfDeg2Nodes(node->rchild);
	if (node->lchild && node->rchild)
		return temp + 1;
	else
		return temp;
}

template<typename T>
int BinaryTree<T>::getNumOfDeg1Nodes() const
{
	return calcNumOfDeg1Nodes(this->root);
}


template<typename T>
int BinaryTree<T>::calcNumOfDeg1Nodes(BinaryTreeNode<T>* node) const
{
	if (!node)
		return 0;

	int temp = calcNumOfDeg1Nodes(node->lchild) + calcNumOfDeg1Nodes(node->rchild);

	if ((node->lchild && !node->rchild) || (node->rchild && !node->lchild))
		return temp + 1;
	else
		return temp;
}

template<typename T>
int BinaryTree<T>::getNumOfLeafNodes() const
{
	//number of leaf nodes in binary tree always equal to number of nodes of deg 2 + 1
	return getNumOfDeg2Nodes() + 1;
}

template<typename T>
void BinaryTree<T>::createBinaryTree()
{
	std::cout << "Enter the root node data : ";
	int data;
	std::cin >> data;
	BinaryTreeNode<int> *root = new BinaryTreeNode<int>(data);
	this->root = root;
	std::queue<BinaryTreeNode<int>*> q;
	q.push(root);
	this->NodesCount++;
	while (!q.empty())
	{
		BinaryTreeNode<int>* element = q.front();
		
		std::cout << "Enter the Left Child of " << element->data << " : ";
		std::cin >> data;
		
		if (data != -1)
		{
			BinaryTreeNode<int>* node = new BinaryTreeNode<int>(data);
			element->lchild = node;
			q.push(node);
			this->NodesCount++;
		}

		std::cout << "Enter the Right Child of " << element->data << " : ";
		std::cin >> data;

		if (data != -1)
		{
			BinaryTreeNode<int>* node = new BinaryTreeNode<int>(data);
			element->rchild = node;
			q.push(node);
			this->NodesCount++;
		}
		q.pop();
	}
}

template<typename T>
bool BinaryTree<T>::is_strict() const
{
	return getNumOfDeg1Nodes() == 0 ? true : false;
}

template<typename T>
bool BinaryTree<T>::is_full() const
{
	double calc = (log(this->NodesCount + 1) / log(2)) - 1;
	int height = getTreeHeight();
	if (calc - (int)calc == 0 && calc == height)
		return true;
	return false;
}

template<typename T>
bool BinaryTree<T>::is_complete() const
{
	// change link representation to array representation
	std::queue<BinaryTreeNode<T>*> q;
	q.push(root);
	Array<int> temp(NodesCount);
	int cnt = 1;
	while (!q.empty())
	{
		BinaryTreeNode<T>* node = q.front();
		if (node->lchild)
		{
			q.push(node->lchild);
			temp.append(cnt);
			cnt++;
		}
		else
			temp.append(-1);
		if (node->rchild)
		{
			q.push(node->rchild);
			temp.append(cnt);
			cnt++;
		}
		else
			temp.append(-1);
		q.pop();
	}

	// check for -1 gaps in the array representation of the tree
	bool mark = false;
	for (int i = 0; i < temp.getLength(); i++)
	{
		if (temp[i] == -1)
			mark = true;
		if (mark && temp[i] != -1)
			return false;
	}
	return true;

}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	std::cout << "tree desctuctor" << std::endl;
	deleteTree(this->root);
	this->NodesCount = 0;
}

template<typename T>
void BinaryTree<T>::deleteTree(BinaryTreeNode<T>* node)
{
	if (!node)
		return;
	deleteTree(node->lchild);
	deleteTree(node->rchild);
	delete node;
}

template<typename T>
int BinaryTree<T>::getNodesCount() const
{
	return this->NodesCount;
}

