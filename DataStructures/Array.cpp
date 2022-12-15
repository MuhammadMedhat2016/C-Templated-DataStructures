#include "Array.h"
#include <cstdlib>
#include<iostream>
using std::cout;
using std::endl;

/*
template<typename Array>
class ArrayIterator
{
public:

	using ValueType = typename Array::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	ArrayIterator(PointerType ptr)
	{
		this->_ptr = ptr;
	}
	ArrayIterator<Array>& operator ++()
	{
		this->_ptr++;
		return *this;
	}
	ArrayIterator<Array>& operator++(int)
	{
		ArrayIterator<Array> temp = *this;
		this->_ptr++;
		return temp;
	}
	ArrayIterator<Array>& operator --()
	{
		this->_ptr--;
		return *this;
	}
	ArrayIterator<Array> operator --(int)
	{
		ArrayIterator<Array> temp = *this;
		this->_ptr--;
		return temp;
	}
	bool operator != (const ArrayIterator<Array>& temp_iter) const
	{
		return this->_ptr != temp_iter._ptr;
	}
	bool operator == (const ArrayIterator<Array>& temp_iter) const
	{
		return this->_ptr == temp_iter._ptr;
	}
	ReferenceType operator * ()
	{
		return *_ptr;
	}
	PointerType operator ->()
	{
		return _ptr;
	}

private:
	PointerType _ptr;
};
*/

template<typename Array>
ArrayIterator<Array>::ArrayIterator(ArrayIterator::PointerType ptr)
{
	this->_ptr = ptr;
}
template<typename Array>
ArrayIterator<Array>& ArrayIterator<Array>::operator ++()
{
	this->_ptr++;
	return *this;
}

template<typename Array>
ArrayIterator<Array> ArrayIterator<Array>::operator ++(int)
{
	ArrayIterator<Array> temp = *this;
	this->_ptr++;
	return temp;
}
template<typename Array>
ArrayIterator<Array>& ArrayIterator<Array>::operator --()
{
	this->_ptr--;
	return *this;
}
template<typename Array>
ArrayIterator<Array> ArrayIterator<Array>::operator --(int)
{
	ArrayIterator<Array> temp = *this;
	this->_ptr--;
	return temp;
}

template<typename Array>
bool ArrayIterator<Array>::operator != (const ArrayIterator<Array>& temp) const
{
	return this->_ptr != temp._ptr;
}
template<typename Array>
bool ArrayIterator<Array>::operator == (const ArrayIterator<Array>& temp_iter) const
{
	return this->_ptr == temp_iter._ptr;
}

template<typename Array>
ArrayIterator<Array>::ReferenceType ArrayIterator<Array>::operator * ()
{
	return *_ptr;
}

template<typename Array>
ArrayIterator<Array>::PointerType ArrayIterator<Array>::operator -> ()
{
	return _ptr;
}

template <class T>
Array<T>::Array()
{
	ptr = nullptr;
	size = 0;
	length = 0;
}

template <class T>
Array<T>::Array(int length)
	:size(size), length(0)
{
	ptr = new T[size];
}

template <class T>
Array<T>::Array(T value, int length)
	:length(length), size(length + 20)
{
	ptr = new int[this->size];
	for (int i = 0; i < length; ++i)
		ptr[i] = value;
}

template <class T>
Array<T>::Array(Array<T> const& arr)
	:size(arr.size), length(arr.length)
{
	this->ptr = new T[this->size];
	for (auto value : arr)
		this->append(value);
}

template <class T>
Array<T>::Array(Array<T>&& arr) noexcept
	:size(arr.size), length(arr.length)
{
	this->ptr = arr.ptr;
	arr.size = 0;
	arr.length = 0;
	arr.ptr = nullptr;
}
template<class T>
Array<T>::Array(List<T>& list)
{
	this->length = 0;
	this->size = list.getLength() + 5;
	this->ptr = new T[this->size];

	for (auto val : list)
		this->append(val);
}

template<typename T>
Array<T>::Array(initializer_list<T> list)
{
	this->length = 0;
	this->size = list.size() + 15;
	this->ptr = new T[this->size];

	for (auto val : list)
		this->append(val);
}

template<class T>
Array<T>::~Array()
{
	delete[]ptr;
}

template <class T>
void Array<T>::append(T value)
{
	if (this->length >= size)
	{
		ptr = (T*)realloc(ptr, sizeof(T) * (this->size + 20));
		this->size += 20;
	}
	ptr[this->length] = value;
	this->length++;
}

template <class T>
T& Array<T>::operator[](const int& idx)
{
	if (idx < 0 || idx > this->length)
		throw std::out_of_range("Provided Index is out of range");
	return ptr[idx];
}


template <class T>
const T& Array<T>::operator[](const int& idx) const
{
	if (idx < 0 || idx > this->length)
		throw std::out_of_range("Provided Index is out of range");
	return ptr[idx];
}

template<class T>
T Array<T>::get(int idx) const
{
	if (idx < 0 || idx >= this->length)
		throw std::out_of_range("Provided Index is out of range");

	return ptr[idx];
}

template <class T>
Array<T> Array<T>::operator + (Array<T>const& arr) const
{
	Array<T> res(this->length + arr.length + 5);
	res.size = this->length + arr.length + 5;
	for (int i = 0; i < this->length; ++i)
		res.append(this->ptr[i]);
	for (int i = 0; i < arr.length; ++i)
		res.append(arr.ptr[i]);
	return res;
}

template <class T>
Array<T>& Array<T>::operator = (Array<T>&& arr) noexcept
{

	delete[] ptr;
	this->size = arr.size;
	this->length = arr.length;
	this->ptr = arr.ptr;

	arr.ptr = nullptr;
	arr.size = arr.length = 0;

	return *this;
}

template <class T>
Array<T>& Array<T>::operator = (Array<T>const& arr)
{
	this->size = arr.size;
	this->length = arr.length;
	this->ptr = new int[arr.size];
	memcpy(this->ptr, arr.ptr, sizeof(T) * arr.length);
	return *this;
}

template<class T>
void Array<T>::sort(bool(*cmp)(const T&, const T&))
{
	this->QuickSort(0, this->length - 1, cmp);
}


template<class T>
void Array<T>::swap(int i, int j)
{
	T temp = this->ptr[i];
	this->ptr[i] = this->ptr[j];
	this->ptr[j] = temp;
}

template<class T>
int Array<T>::Partition(int p, int r, bool(*cmp)(T const&, T const&))
{
	int pivot = p + rand() % (r - p + 1);
	swap(pivot, r);
	T temp = this->ptr[r];
	int idx = p - 1;
	for (int i = p; i <= r - 1; ++i)
	{
		if (cmp == NULL && this->ptr[i] < temp)
		{
			swap(i, idx + 1);
			idx++;
		}
		else if (cmp != NULL && cmp(this->ptr[i], temp))
		{
			swap(i, idx + 1);
			idx++;
		}
	}
	swap(idx + 1, r);
	return idx + 1;
}

template<class T>
void Array<T>::QuickSort(int p, int r, bool(*cmp)(T const&, T const&))
{
	if (p >= r) return;
	int q = Partition(p, r, cmp);
	QuickSort(p, q - 1, cmp);
	QuickSort(q + 1, r, cmp);
}

template<class T>
int Array<T>::getLength() const
{
	return this->length;
}

template<class T>
void Array<T>::insert(int idx, T value)
{
	if (idx < 0 && idx > this->length)
		throw std::out_of_range("Provided Index is out of range");
	this->append(value);
	int curIdx = this->length - 1;
	while (curIdx > idx)
	{
		this->swap(curIdx, curIdx - 1);
		curIdx--;
	}
}

template<class T>
T Array<T>::remove(int idx)
{
	if (idx < 0 && idx >= this->length)
		throw std::out_of_range("Provided Index is out of range");
	T temp = this->ptr[idx];
	while (idx != this->length - 1)
	{
		this->swap(idx, idx + 1);
		idx++;
	}
	this->length--;
	return temp;
}

template<class T>
void Array<T>::set(int idx, T value)
{
	if (idx < 0 || idx >= length)
		throw std::out_of_range("Provided Index is out of range");
	this->ptr[idx] = value;
}

template<class T>
T Array<T>::max() const
{
	T mx = this->ptr[0];
	for (int i = 0; i < this->length; ++i)
	{
		if (this->ptr[i] > mx)
			mx = this->ptr[i];
	}
	return mx;
}

template<class T>
T Array<T>::min() const
{
	T mn = this->ptr[0];
	for (int i = 0; i < this->length; ++i)
	{
		if (this->ptr[i] < mn)
			mn = this->ptr[i];
	}
	return mn;
}

template<class T>
void Array<T>::reverse()
{
	int l = 0, r = this->length - 1;
	while (l <= r)
	{
		this->swap(l, r);
		l++;
		r--;
	}
}

template<class T>
void Array<T>::rotate()
{
	if (this->length == 0)
		return;
	T temp = this->ptr[0];
	this->remove(0);
	this->append(temp);
}

template<class T>
bool Array<T>::search(T key, bool applyOptimization)
{
	for (int i = 0; i < this->length; ++i)
		if (this->ptr[i] == key)
		{
			// tansposition optimization method
			if (applyOptimization && i != 0) swap(i, i - 1);
			return true;
		}
	return false;
}

template<class T>
Array<T> Array<T>::remove_dublicates() const
{
	Array<T> temp = *this, res = Array<T>(this->length);
	temp.sort();
	for (int i = 0; i < temp.length; ++i)
	{
		if (res.length > 0 && temp[i] == res.ptr[res.length - 1])
			continue;
		res.append(temp[i]);
	}
	return res;
}

template<class T>
Array<T> Array<T>::Union(Array<T> const& arr) const
{
	//nlog(n) solution
	// removing duplicates
	Array<T> temp1 = this->remove_dublicates();
	Array<T> temp2 = arr.remove_dublicates();
	Array<T> res(temp1.length + temp2.length);
	int i, j;
	i = j = 0;
	while (i < temp1.length && j < temp2.length)
	{
		if (temp1[i] == temp2[j])
		{
			res.append(temp1[i]);
			i++;
			j++;
		}
		else if (temp1[i] < temp2[j])
		{
			res.append(temp1[i]);
			i++;
		}
		else
		{
			res.append(temp2[j]);
			j++;
		}
	}
	for (; i < temp1.length; ++i)
		res.append(temp1[i]);
	for (; j < temp2.length; ++j)
		res.append(temp2[j]);
	return res;
}
template<class T>

Array<T> Array<T>::Intersection(Array<T> const& arr) const
{
	//nlog(n) solution
	// removing dublicates
	Array<T> temp1 = this->remove_dublicates();
	Array<T> temp2 = arr.remove_dublicates();
	Array<T> res(temp1.length + temp2.length);
	int i, j;
	i = j = 0;
	while (i < temp1.length && j < temp2.length)
	{
		if (temp1[i] < temp2[j])
			i++;
		else if (temp1[i] > temp2[j])
			j++;
		else
		{
			res.append(temp1[i]);
			i++;
			j++;
		}
	}
	return res;
}

template<class T>
Array<T> Array<T>::Difference(Array<T> const& arr) const
{
	Array<T> temp1 = this->remove_dublicates();
	Array<T> temp2 = arr.remove_dublicates();
	Array<T> res(temp1.length + temp2.length);
	int i, j;
	i = j = 0;
	while (i < temp1.length && j < temp2.length)
	{
		if (temp1[i] > temp2[j])
		{
			j++;
		}
		else if (temp1[i] == temp2[j])
		{
			i++;
			j++;
		}
		else
		{
			res.append(temp1[i]);
			i++;
		}
	}
	for (; i < temp1.length; ++i)
		res.append(temp1[i]);
	return res;
}

template<typename T>
Array<T>::Iterator Array<T>::begin()
{
	return Array<T>::Iterator(this->ptr);
}

template<typename T>
Array<T>::Iterator Array<T>::end()
{
	return Array<T>::Iterator(this->ptr + length);
}



