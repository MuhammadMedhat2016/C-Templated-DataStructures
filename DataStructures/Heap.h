#pragma once

#include <initializer_list>
using std::initializer_list;
#include <cmath>

template<typename T>
class Array;

template<typename T>
class List;

// _NODISCARD means that the return value of method or function must be used properly not simply discarded 
// the compiler will generate warning if you discard the returning value

template<typename T = void>
struct Greater
{
	_NODISCARD constexpr bool operator() (const T& _Left, const T& _Right) const
	{
		return _Left > _Right;
	}
};

template<typename T = void>
struct Less
{
	_NODISCARD constexpr bool operator() (const T& _Left, const T& _Right) const
	{
		return _Left < _Right;
	}
};
template<typename T, typename C>
struct isLess;

template<typename T>
struct isLess <T, Less<T>>
{
	static constexpr bool value = true;
};

template<typename T>
struct isLess <T, Greater<T>>
{
	static constexpr bool value = false;
};

template<typename T, typename C = Less<T>>
class Heap
{
public:
	Heap();
	Heap(const T[], size_t);
	Heap( Array<T>&);
	Heap( List<T>&);
	Heap(initializer_list<T>);
	Heap(Heap<T,C>& heap);
	Heap(Heap<T,C>&& heap);
	Array<T> HeapSort();
	void insert(const T& value);
	void heapify();
	T remove();
	void showHeap();
	int size();
	~Heap();
private: 
	void heapify(int idx);
	void remove(int idx);
	Array<T>* heap_values;
	int heap_size;
	C comp{};
};
