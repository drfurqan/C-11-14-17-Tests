/********************************************************************
created:	2018/06/07
created:	07:06:2018   22:11
filename: 	variadic_template_2.cpp
file base:	variadic_template_2
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk

purpose:	How to use and implement variadic templates?

/*******************************************************************/

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

// Description:
// Base function of variadic template
// This base function will be the last call of the 
// main variadic template function.
static void createStream(std::ostream& _o)
{
}

// Description:
// Main variadic template function
// This function will be called from the last argument
// to the first argument (in descending order).
// Note: To count the number of arguments called
// std::cout << "count: " << sizeof...(_args) << "\n";
template <class _First, class... _Rest>
static void createStream(std::ostream& _o, const _First& _value, const _Rest&... _rest)
{
	_o << _value;
	createStream(_o, _rest...);
}

// Description:
// Main function that concatenate all the specifying parameters
// and returns as a string.
template <class... _T>
static std::string concatenate(const _T&... _value)
{
	std::ostringstream o;
	createStream(o, _value...);
	return o.str();
}

int main(int argc, char* argv[])
{
	std::cout << concatenate(2018, '-', 06, '-', 07) << "\n";
	std::cout << concatenate("Vertex Position is ", std::fixed, std::setprecision(2), 5 / 100.0, " at left corner.") << "\n";

	return std::cin.get();
}