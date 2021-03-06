/********************************************************************
created:	2017/01/09
created:	09:01:2017   22:11
filename: 	variadic_template.cpp
file base:	variadic_template
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk

purpose:	How to use and implement variadic templates?

/*******************************************************************/

#include <iostream>

// Base function of variadic template
// This base function will be the last call of the 
// main variadic template function.
template <typename _T>
void Printf(const _T& _v)
{
	std::cout << _v << "\n";
}

// Main variadic template function
// This function will be called from the last argument
// to the first argument (in descending order).
// Note: To count the number of arguments called
// std::cout << "count: " << sizeof...(_args) << "\n";
// Remember: above count code will only be called (N-1)
// arguments, the last count will be printed out by the
// Base Function.
template <typename _T, typename... _Types>
void Printf(const _T& _first, const _Types&... _args)
{
	std::cout << _first << "\n";
	//std::cout << "count: "<< sizeof...(_args) << "\n";
	Printf(_args...);
}

int main()
{
	Printf(1, 2, 3, 4, "5", "\n");

	Printf("one", 'C', 2.4, 5.1f, "last");

	return 0;
}

