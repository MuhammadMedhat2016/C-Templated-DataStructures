#include "Polynomial.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::pair;

template <typename T>
Polynomial<T, true>::Polynomial(int n)
	:n(n)
{
	term = Array<pair<int, T>>(n);
}

template<class T>
void Polynomial<T, true>::init()
{
	cout << "Enter the exponent first then coefficient of that exponent in pairs" << endl;
	for (int i = 0; i < n; ++i)
	{
		pair<int, T> temp;
		cin >> temp.first >> temp.second;
		term.append(temp);
	}
}

template<class T>
T Polynomial<T, true>::evaluate(T x)
{
	T sum = T(0.0);
	for (int i = 0; i < n; ++i)
	{
		sum += term[i].second * calculate_power(x, term[i].first);
	}
	return sum;
}

template<class T>
bool cmp(pair<int, T>const& p1, pair<int, T>const& p2)
{
	return p1.first > p2.first;
}

template<class T>

Polynomial<T> Polynomial<T, true>::operator + (Polynomial<T> poly)
{
	this->term.sort(cmp);
	poly.term.sort(cmp);

	int i, j;
	i = j = 0;
	Polynomial<T> temp(this->term.getLength() + poly.term.getLength());
	while (i < this->n && j < poly.n)
	{
		if (this->term[i].first == poly.term[j].first)
		{
			temp.term.append({ term[i].first , this->term[i].second + poly.term[j].second });
			i++; j++;
		}
		else if (this->term[i].first > poly.term[j].first)
		{
			temp.term.append(this->term[i]);
			i++;
		}
		else
		{
			temp.term.append(poly.term[j]);
			j++;
		}
	}
	for (; i < this->term.getLength(); i++)
		temp.term.append(this->term[i]);

	for (; j < poly.term.getLength(); j++)
		temp.term.append(poly.term[j]);

	return temp;
}
template<class T>
void Polynomial<T, true>::display()
{
	cout << "Exponent " << " - " << "Coefficient" << endl;
	for (int i = 0; i < this->term.getLength(); ++i)
	{
		cout << this->term[i].first << "------" << this->term[i].second << endl;
	}
}

template<class T>
T calculate_power(T base, int exponent)
{
	//this piece of code for making sure that only int, float and double are the valid types for this class
	// static assertion is used for checking if a condition is true or not at compile time
	//static_assert(std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value);
	// O(log(n)) 
	if (exponent == 0) return 1;
	else if (exponent == 1) return base;

	if (exponent % 2)
		return base * calculate_power(base, exponent - 1);
	else
	{
		T temp = calculate_power(base, exponent / 2);
		return temp * temp;
	}

}
