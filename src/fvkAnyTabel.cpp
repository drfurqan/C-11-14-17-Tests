/**********************************************************************************
created:	2017/01/01
created:	01:01:2017   22:11
filename: 	fvkAnyTabel.cpp
file base:	fvkAnyTabel
file ext:	cpp
author:		Furqan Ullah (Post-doc, Ph.D.)
website:    http://real3d.pk
CopyRight:	All Rights Reserved

purpose:	class to create a tabel of Key and Value using C++17 std::any.
It accepts any data type as a value to the string key and then later retrieve
the value of the desired key.

1. There will not be any duplicate variable in the macro table because of
unordered_map container.
2. It will throw an error message of bad casting and invalid key value in
calling get() function.

/**********************************************************************************
*	Fast Visualization Kit (FVK)
*	REAL3D
**********************************************************************************/

#include <any>				// since C++17
#include <optional>			// since C++17
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class fvkAnyTabel
{
public:
	// Description:
	// Function to add a variable name and its value to the table.
	template<typename _T>
	void add(const std::string& _name, _T _value)
	{
		m_list[_name] = std::make_any<_T>(_value);
	}

	// Description:
	// Function to get the value of the given variable name.
	template<typename _T>
	std::optional<_T> get(const std::string& _name)
	{
		if (m_list.find(_name) != m_list.end())
		{
			const auto& v = m_list[_name];
			if (v.has_value())
			{
				try
				{
					return std::any_cast<_T>(v);	// throws bad any cast.
				}
				catch (const std::bad_any_cast& _e)
				{
					std::string msg(std::string("Error: casting from '") + _name + std::string("' throws ") + _e.what());
					std::cerr << msg << "!\n";
					throw std::runtime_error(msg);
				}
			}
		}

		return std::nullopt;
	}

	// Description:
	// Function to clear the table.
	void clear() { m_list.clear(); }

	// Description:
	// Function to get the size of the table.
	auto size() const { return m_list.size(); }

private:
	std::unordered_map<std::string, std::any> m_list;
};

int main()
{
	// adding different types to the table.
	fvkAnyTabel o;
	o.add("int", 1);
	o.add("float", 3.5f);
	o.add("double", 2.2);
	o.add("const char*", "const char*");
	o.add("std::string", std::string("std::string"));

	// its possible to add even any STL container.
	o.add("vector_values", std::vector<int>{2, 1, 3});

	// retrieving values from the table by specifying the name of the variable.
	std::cout << "int: " << *o.get<int>("int") << "\n";
	std::cout << "float: " << *o.get<float>("float") << "\n";
	std::cout << "double: " << *o.get<double>("double") << "\n";
	std::cout << "const char*: " << *o.get<const char*>("const char*") << "\n";
	std::cout << "std::string: " << *o.get<std::string>("std::string") << "\n\n";

	std::cout << "Vector Values...\n\n";

	// retrieving STL container from the table.
	auto op = o.get<std::vector<int>>("vector_values");
	if (op.has_value())
	{
		auto v = op.value();
		std::cout << "size: " << v.size() << "\n";
		for (const auto& i : v)
			std::cout << i << "\n";
	}

	std::cout << "\nchecking unknowns...\n\n";

	// checking unknown value
	// exception will be thrown if we don't check with has_value().
	auto v = o.get<int>("unknown");
	if (v.has_value())
		std::cout << "unknown: " << v.value() << "\n";
	else
		std::cout << "couldn't find any variable with this name!\n";

	return 0;
}