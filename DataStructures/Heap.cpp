#include "Heap.h"
#include <iostream>
using namespace std;



template<typename T,typename C>
Heap<T, C>::Heap()
{
	heap_values = new Array<T>();
	heap_size = 0;
}

template<typename T, class C>
Heap<T, C>::Heap(const T arr[], size_t size)
{
	heap_values = new Array<T>(size + 10);
	for (int i = 0; i < size; ++i)
		heap_values->append(arr[i]);
	this->heap_size = size;
	heapify();
}


template<typename T, class C>
Heap<T,C>::Heap(Array<T>& arr)
{
	heap_values = new Array<T>(arr.getLength() + 10);
	for (auto element : arr)
		heap_values->append(element);
	this->heap_size = arr.getLength();
	heapify();
}

template<typename T, class C>
Heap<T, C>::Heap( List<T>& list)
{
	heap_values = new Array<T>(list.getLength() + 10);
	for (auto element : list)
		this->heap_values->append(element);
	this->heap_size = list.getLength();
	heapify();
}

template<typename T, class C>
Heap<T, C>::Heap(initializer_list<T> list)
{
	heap_values = new Array<T>(list.size() + 10);
	for (auto element : list)
		this->heap_values->append(element);
	this->heap_size = list.size();
	this->heapify();
}

template<typename T, class C>
Heap<T, C>::Heap(Heap<T,C>&& heap)
{
	this->heap_values = heap.heap_values;
	this->heap_size = this->heap_size;

	heap.heap_values = nullptr;
	heap.heap_size = -1;
}
template<typename T, class C>
Heap<T, C>::Heap( Heap<T,C>& heap)
{
	this->heap_values = new Array<T>();
	for (int i = 0; i < heap.size(); ++i)
	{
		this->heap_values->append((*heap.heap_values)[i]);
	}
	this->heap_size = heap.size();
}
template<typename T, class C>
int Heap<T, C>::size()
{
	return this->heap_size;
}

template<typename T, class C>
Heap<T, C>::~Heap()
{
	delete this->heap_values;
}

template<typename T, class C>
void Heap<T, C>::insert(const T& value)
{
	this->heap_values->append(value);
	this->heap_size++;

	int i;
	i = this->heap_size -1;
	while (i)
	{
		int parentIndex = int(ceil(((double)(i) / 2.0) - 1));
		bool bol = comp((*heap_values)[parentIndex], (*heap_values)[i]);
		if (bol)
			std::swap((*heap_values)[i], (*heap_values)[parentIndex]);
		else
			break;
		i = parentIndex;
	}
}

template<typename T, typename C>
void Heap<T, C>::heapify()
{
	// the complete Binary tree has a feature to get the index of leaf nodes quickly using a formula for ZERO Based Array representation
	// which is (leaf_nodes_indices) = {n/2 to n} then the last non-leaf node is at (n/2)-1 we shall start from there
	// O(n)
	for (int i = (this->heap_size / 2)-1; i >= 0; i--)
		heapify(i);
}

template<typename T, typename C>
void Heap<T, C>::heapify(int index)
{
	int temp = index, lchild = index * 2 + 1, rchild = index * 2 + 2;
	if (lchild < this->heap_size && comp((*heap_values)[temp], (*heap_values)[lchild]))
		temp = lchild;
	if (rchild < this->heap_size && comp((*heap_values)[temp], (*heap_values)[rchild]))
		temp = rchild;
	// for max-heap temp would have the largest element among these three values 
	// for min-heap temp would have the smallest element among these three element
	if (temp != index)
	{
		swap((*heap_values)[temp], (*heap_values)[index]);
		heapify(temp);
	}
}
template<typename T, class C>
void Heap<T, C>::showHeap()
{
	for (int i = 0; i < this->heap_size; ++i)
		cout << (*heap_values)[i] << " ";
	cout << endl;
}
template<typename T, class C>
T Heap<T, C>::remove()
{
	swap((*heap_values)[0], (*heap_values)[heap_size - 1]);
	T ret = (*heap_values)[heap_size - 1];
	this->heap_size--;
	remove(0);
	return ret;
}
template<typename T, class C>
void Heap<T, C>::remove(int index)
{
	int temp = index, lchild = index * 2 + 1, rchild = index * 2 + 2;
	if (lchild < this->heap_size && comp((*heap_values)[temp], (*heap_values)[lchild]))
		temp = lchild;
	if (rchild < this->heap_size && comp((*heap_values)[temp], (*heap_values)[rchild]))
		temp = rchild;

	if (temp != index)
	{
		swap((*heap_values)[temp], (*heap_values)[index]);
		remove(temp);
	}
}

template<typename T, typename C>
Array<T> Heap<T, C>::HeapSort()
{
	Array<T> ret;
	if constexpr (isLess<T, C>::value)
	{
		Heap<T> temp = *this;
		int n = this->heap_size;
		for (int i = 0; i < n; ++i)
			ret.append(temp.remove());
		ret.reverse();
	}
	if constexpr (!isLess<T, C>::value)
	{
		Heap<T, Greater<T>> temp = *this;
		int n = this->heap_size;
		for (int i = 0; i < n; ++i)
			ret.append(temp.remove());
	}
	return ret;
}




