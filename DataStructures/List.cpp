#include "List.h"
#include <cstdlib>
#include<iostream>

using std::cout;
using std::endl;


template<typename list>
ListIterator<list>::ListIterator()
{
	this->_ptr = nullptr;
}
template<typename list>
ListIterator<list>::ListIterator(ListIterator::NodePointerType ptr)
	:_ptr(ptr)
{}

template<typename list>
ListIterator<list>& ListIterator<list>::operator++()
{
	this->_ptr = this->_ptr->next;
	return *this;
}
template<typename list>
ListIterator<list> ListIterator<list>::operator++(int)
{
	ListIterator<list> temp = *this;
	this->_ptr = this->_ptr->next;
	return temp;
}
template<typename list>
bool ListIterator<list>::operator != (const ListIterator<list>& temp) const
{
	return this->_ptr != temp._ptr;
}

template<typename list>
bool ListIterator<list>::operator == (const ListIterator<list>& temp) const
{
	return this->ptr == temp._ptr;
}

template<typename list>
ListIterator<list>::ReferenceValueType ListIterator<list>::operator * ()
{
	return this->_ptr->data;
}

template<typename list>
ListIterator<list>::PointerValueType ListIterator<list>::operator -> ()
{
	ListIterator::PointerValueType ret = &(this->_ptr->data);
	return ret;
}

template<class T>
Node<T>::Node(T data)
	:data(data)
{
	this->next = nullptr;
}

template<class T>
List<T>::List()
{
	this->head = this->tail = nullptr;
	this->length = 0;
}

template<class T>
List<T>::List(List<T>const& list)
{
	this->head = this->tail = nullptr;
	this->length = 0;
	Node<T>* temp = list.head;
	while (temp)
	{
		Node<T>* node = new Node<T>(temp->data);
		if (temp == list.head)
			this->head = this->tail = node;
		else
		{
			this->tail->next = node;
			this->tail = node;
		}
		temp = temp->next;
	}
	this->length = list.length;
}

template<class T>
List<T>::List(Array<T>& arr)
{
	this->head = this->tail = nullptr;
	this->length = 0;
	for (auto value : arr)
		this->append(value);
}

template<class T>
List<T>::List(List<T>&& list) noexcept
{
	cout << "move ctor of list" << endl;

	this->head = list.head;
	this->tail = list.tail;
	this->length = list.length;

	list.head = nullptr;
	list.tail = nullptr;
	list.length = 0;
}

template<class T>
List<T>::List(T const* const arr, int size)
{
	this->head = this->tail = nullptr;
	for (int i = 0; i < size; ++i)
	{
		Node<T>* node = new Node<T>(arr[i]);
		if (i == 0)
			this->head = this->tail = node;
		else
		{
			this->tail->next = node;
			this->tail = node;
		}
	}
	this->length = size;
}

template<typename T>
List<T>::List(initializer_list<T> list)
{
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;

	for (auto val : list)
		this->append(val);

}
template<class T>
List<T>& List<T>::operator = (List<T> const& list)
{
	Node<T>* temp = list.head;
	while (temp)
	{
		Node<T>* node = new Node<T>(temp->data);
		if (temp == list.head)
			this->head = this->tail = node;
		else
		{
			this->tail->next = node;
			this->tail = node;
		}
		temp = temp->next;
	}
	this->length = list.length;
	return *this;
}
template<class T>
List<T>& List<T>::operator = (List<T>&& list) noexcept
{

	this->~List();
	this->head = this->tail = nullptr;
	this->length = 0;


	this->head = list.head;
	this->tail = list.tail;

	list.head = list.tail = nullptr;
	return *this;
}

template<class T>
int List<T>::getLength() const
{
	return this->length;
}

template <class T>
List<T>::~List()
{
	Node<T>* current = this->head;
	while (current)
	{
		Node<T>* temp = current;
		current = current->next;
		delete temp;
	}
}
template <class T>
T List<T>::max() const
{
	if (this->head == nullptr)
		throw new std::range_error("the specified index is out of range");

	Node<T>* temp = this->head;
	T res = this->head->data;
	while (temp)
	{
		res = res > temp->data ? res : temp->data;
		temp = temp->next;
	}
	return res;
}
template <class T>
T List<T>::min() const
{
	if (this->head == nullptr)
		throw new std::range_error("the specified index is out of range");
	Node<T>* temp = this->head;
	T res = this->head->data;
	while (temp)
	{
		res = res < temp->data ? res : temp->data;
		temp = temp->next;
	}
	return res;
}
template <class T>
int List<T>::search(const T key, bool applyOptimization)
{
	Node<T>* p, * q;
	p = q = this->head;
	int i = 0;
	while (p)
	{
		if (p->data == key)
		{
			if (applyOptimization)
			{
				q->next = p->next;
				p->next = q == p ? this->head->next : this->head;
				this->head = p;
				return 0;
			}
			return i;
		}
		i++;
		q = p;
		p = p->next;
	}
	return -1;
}
template<class T>
void List<T>::insert(int idx, T value)
{
	if (idx < 0 || idx > this->length)
		throw new std::out_of_range("the specified index is out of range");

	Node<T>* node = new Node<T>(value);

	if (this->head == nullptr)
	{
		this->head = this->tail = node;
		this->length = 1;
		return;
	}
	if (idx == 0)
	{
		node->next = this->head;
		this->head = node;
	}
	else if (idx == this->length)
	{
		this->tail->next = node;
		this->tail = node;
	}
	else
	{
		Node<T>* temp = this->head;
		for (int i = 0; i < idx - 1; ++i)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
	this->length++;
}
template<class T>
void List<T>::sort(bool(*cmp)(T const&, T const&))
{
	Array<T> temp = *this;
	temp.sort(cmp);
	*this = temp;
	this->length = temp.getLength();
}

template<class T>
void List<T>::append(T value)
{
	Node<T>* temp = new Node<T>(value);
	if (this->head == nullptr)
	{
		this->head = this->tail = temp;
		this->length = 1;
		return;
	}
	this->tail->next = temp;
	this->tail = temp;
	this->length++;
}

template<class T>
T& List<T>::operator [] (const int& index)
{
	if (index < 0 || index >= this->length)
		throw new std::out_of_range("the specified index is out of range");

	Node<T>* ptr = this->head;
	for (int i = 0; i < index; ++i)
		ptr = ptr->next;
	return ptr->data;
}
template<class T>
const T& List<T>::operator [] (const int& index) const
{
	if (index < 0 || index >= this->length)
		throw new std::out_of_range("the specified index is out of range");
	Node<T>* ptr = this->head;
	for (int i = 0; i < index; ++i)
		ptr = ptr->next;
	return ptr->data;
}

template<class T>
T List<T>::get(int index)
{
	if (index < 0 || index >= this->length)
		throw new std::out_of_range("the specified index is out of range");
	Node<T>* ptr = this->head;
	for (int i = 0; i < index; ++i)
		ptr = ptr->next;
	return ptr->data;
}

template<class T>
int List<T>::getIndex(T const& value) const
{
	Node<T>* temp = this->head;
	int i = 0;
	while (temp)
	{
		if (value == temp->data)
			return i;
		temp = temp->next;
		i++;
	}
	return -1;
}

template<class T>
T List<T>::removeByIndex(int index)
{
	if (index < 0 || index >= length)
		throw new std::out_of_range("the specified index is out of range");
	Node<T>* q = nullptr, * temp = this->head;
	if (index == 0)
		this->head = this->head->next;
	else
	{
		for (int i = 0; i <= index - 1; ++i)
		{
			q = temp;
			temp = temp->next;
		}
		q->next = temp->next;;
		if (index == this->length - 1)
			this->tail = q;
	}
	T ret = temp->data;
	this->length--;
	delete temp;
	return ret;
}
template<class T>
int List<T>::removeByValue(T value)
{
	Node<T>* q = nullptr, * temp = this->head;
	int i = 0;
	if (value == this->head->data)
		this->head = this->head->next;
	else
	{
		while (temp && temp->data != value)
		{
			i++;
			q = temp;
			temp = temp->next;
		}
		if (temp == nullptr)
			return -1;
		if (temp->next == nullptr)
			this->tail = q;
		q->next = temp->next;

	}
	delete temp;
	this->length--;
	return i;
}

template<class T>
List<T> List<T>::operator + (List<T> const& list) const
{
	List<T> temp = *this;
	Node<T>* p = list.head;
	while (p)
	{
		temp.append(p->data);
		p = p->next;
	}
	return temp;
}

template<typename T>
List<T> List<T>::removeDublicates() const
{
	List<T> list = *this;
	list.sort();
	Node<T>* p, * q;
	p = list.head->next;
	q = list.head;
	while (p)
	{
		if (q->data == p->data)
		{
			q->next = p->next;
			delete p;
			p = q->next;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	return list;
}

template <typename T>
void List<T>::reverse()
{
	Node<T>* p, * q, * r;
	p = this->head;
	q = r = nullptr;

	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	Node<T>* temp;
	temp = this->tail;
	this->tail = this->head;
	this->head = temp;
}

template<typename T>
List<T>::Iterator List<T>::begin()
{
	return Iterator(this->head);
}

template<typename T>
List<T>::Iterator List<T>::end()
{
	return Iterator(nullptr);
}

template<typename T>
List<T> Merge(List<T> list1, List<T> list2)
{
	list1.sort();
	list2.sort();

	List<T> ret;
	ret.head = ret.tail = nullptr;
	ret.length = list1.length + list2.length;
	// safety checks 
	if (!list1.head)
	{
		ret.head = list2.head;
		ret.tail = list2.tail;
		list2.head = list2.tail = nullptr;
		return ret;
	}
	else if (!list2.head)
	{
		ret.head = list1.head;
		ret.tail = list1.tail;
		list1.head = list1.tail = nullptr;
		return ret;
	}

	if (list1.head->data < list2.head->data)
	{
		ret.head = ret.tail = list1.head;
		list1.head = list1.head->next;
		ret.tail->next = nullptr;
	}
	else
	{
		ret.head = ret.tail = list2.head;
		list2.head = list2.head->next;
		ret.tail->next = nullptr;
	}

	while (list1.head && list2.head)
	{
		if (list1.head->data < list2.head->data)
		{
			ret.tail->next = list1.head;
			ret.tail = list1.head;
			list1.head = list1.head->next;
			ret.tail->next = nullptr;
		}
		else
		{

			ret.tail->next = list2.head;
			ret.tail = list2.head;
			list2.head = list2.head->next;
			ret.tail->next = nullptr;
		}
	}

	if (list1.head)
	{
		ret.tail->next = list1.head;
		ret.tail = list1.tail;
		list1.head = list1.tail = nullptr;
	}

	if (list2.head)
	{
		ret.tail->next = list2.head;
		ret.tail = list2.tail;
		list2.head = list2.tail = nullptr;
	}

	return ret;
}