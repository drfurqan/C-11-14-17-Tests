/********************************************************************
created:	2017/01/09
created:	09:01:2017   22:11
filename: 	std_optional.cpp
file base:	std_optional
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk

purpose:	How to use and implement std::optional?

/*******************************************************************/

#include <iostream>
#include <vector>
#include <optional>


std::optional< std::vector<int> > getValues(int _size)
{
	if (_size == 0)
		return std::nullopt;

	std::vector<int> v(_size, _size);

	return v;
}

int main()
{
	//auto v = getValues(0);
	auto v = getValues(3);
	if (v)
	{
		std::cout << "not nullptr\n";
		for (auto i : *v)
			std::cout << i << "\n";
	}
	else
	{
		std::cout << "nullptr\n";
	}

	// OR

	std::cout << "OR\n";
	if (v.has_value())
	{
		auto val = v.value();
		for (auto i : val)
			std::cout << i << "\n";
	}

	return 0;
}

