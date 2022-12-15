#pragma once

#include<initializer_list>
#include "List.h"

using std::initializer_list;

template<class T>
class Node;

template<class T>
class Linkedlist;

template<typename Array>
class ArrayIterator
{
public:

	using ValueType = typename Array::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	ArrayIterator(PointerType ptr);
	ArrayIterator<Array>& operator ++();
	ArrayIterator<Array> operator++(int);
	ArrayIterator<Array>& operator --();
	ArrayIterator<Array> operator --(int);
	bool operator != (const ArrayIterator<Array>& temp_iter) const;
	bool operator == (const ArrayIterator<Array>& temp_iter) const;
	ReferenceType operator * ();
	PointerType operator ->();
private:
	PointerType _ptr;
};

template <class T>
class Array
{
private:
	T* ptr;
	int size;
	int length;
	void QuickSort(int p, int r, bool(*cmp)(T const&, T const&) = NULL);
	int Partition(int p, int r, bool(*cmp)(T const&, T const&) = NULL);
	void swap(int i, int j);
	Array<T> remove_dublicates() const;
public:

	using ValueType = T;
	using const_ref = const T&;
	using _ref = T&;
	using const_ptr = const T*;
	using _ptr = T*;
	using Iterator = ArrayIterator<Array<T>>;

	Array();
	Array(int length);
	Array(T value, int length);
	Array(Array<ValueType> const& arr);
	Array(Array<ValueType>&& arr) noexcept;
	Array(List<ValueType>&);
	Array(initializer_list<ValueType> list);
	void append(T value);
	int getLength() const;
	void insert(int idx, ValueType value);
	ValueType remove(int idx);
	bool search(ValueType key, bool applyOptimization = false);
	void sort(bool (*cmp)(const_ref, const_ref) = NULL);
	ValueType get(int idx) const;
	void set(int idx, ValueType value);
	ValueType max() const;
	ValueType min() const;
	Iterator begin();
	Iterator end();
	Array<ValueType> Union(Array<ValueType> const& array) const;
	Array<ValueType> Intersection(Array<ValueType>const& array) const;
	Array<ValueType> Difference(Array<ValueType>const& array) const;
	~Array();
	void reverse();
	void rotate();
	const_ref operator[](const int& idx) const;
	_ref operator[](const int& idx);
	Array<ValueType> operator + (Array<ValueType> const& arr) const;
	Array<ValueType>& operator = (Array<ValueType>&& arr) noexcept;
	Array<ValueType>& operator = (Array<ValueType>const& arr);
};