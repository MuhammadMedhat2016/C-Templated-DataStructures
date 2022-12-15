#pragma once
#include <utility>
#include "Array.h"
using std::pair;



template<typename T, typename U>
struct is_same
{
	static bool constexpr value = false;
};
template<typename T>
struct is_same<T, T>
{
	static bool constexpr value = true;
};

template<typename T>
struct is_numeric
{
	static constexpr bool value = false;
};
template<>
struct is_numeric<int>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<short>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<long>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<long long>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<float>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<double>
{
	static constexpr bool value = true;
};
template<>
struct is_numeric<long double>
{
	static constexpr bool value = true;
};

template <typename T, bool = (is_numeric<T>::value) >
class Polynomial;

template <typename T>
class Polynomial<T, true>
{
private:
	Array<std::pair<int, T>> term;
	int n;
public:
	Polynomial(int n);
	void init();
	T evaluate(T x);
	Polynomial<T> operator + (Polynomial<T> poly);
	void display();
};

template<typename T>
T calculate_power(T base, int exponent);


template<class T>
bool cmp(const pair<int, T>&, const pair<int, T>&);

