#pragma once

#include<initializer_list>
using std::initializer_list;

template<class T>
class Array;

template<class T>
class Node
{
public:
	T data;
	Node* next;
	Node(T data);
};

template<typename list>
class ListIterator
{
	using NodeValueType = typename list::NodeValueType;
	using ValueType = typename list::ValueType;
	using ReferenceValueType = ValueType&;
	using PointerValueType = ValueType*;
	using NodePointerType = NodeValueType*;
	using NodeReferenceType = NodeValueType&;
public:
	ListIterator();
	ListIterator(NodePointerType ptr);
	ListIterator<list>& operator ++();
	ListIterator<list> operator++(int);
	bool operator != (const ListIterator<list>&) const;
	bool operator == (const ListIterator<list>&) const;
	ReferenceValueType operator * ();
	PointerValueType operator ->();
private:
	NodePointerType _ptr;
};

template<class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int length;
public:

	using ValueType = T;
	using PointerValueType = T*;
	using NodeValueType = Node<T>;
	using NodePointerType = Node<T>*;
	using const_NodePointerType = const Node<T>*;
	using NodeReferenceType = Node<T>&;
	using const_NodeReferenceType = const Node<T>&;
	using Iterator = ListIterator<List<T>>;

	List();
	List(List<T> const& list);
	List(Array<T>& arr);
	List(List<T>&& list) noexcept;
	List(T const* const arr, int size);
	List(initializer_list<T> list);
	List<T>& operator = (List<T> const& list);
	List<T>& operator = (List<T>&& list) noexcept;
	int getLength() const;
	T max() const;
	T min() const;
	int search(const T key, bool applyOptimization = false);
	void insert(int idx, T value);
	void sort(bool(*cmp)(T const&, T const&) = nullptr);
	void append(T value);
	T& operator [] (const int& index);
	const T& operator [] (const int& index) const;
	List<T> operator + (List<T> const&) const;
	T get(int index);
	int getIndex(T const& value) const;
	T removeByIndex(int index);
	int removeByValue(T value);
	List<T> removeDublicates() const;
	void reverse();
	~List();
	Iterator begin();
	Iterator end();
	template<typename type>
	friend List<type> Merge(List<type> list1, List<type> list2);
};
