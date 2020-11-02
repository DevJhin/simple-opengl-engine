#pragma once
#include <type_traits>

class Type
{
public:
	template<class Base, class Derived>
	static bool IsChildOf()
	{
		return std::is_base_of<Base, Derived>();
	}

};
