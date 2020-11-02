#pragma once
#include "StringTypes.h"

class Object
{
public:
	virtual ~Object() = default;
	String name;

	virtual String ToString()
	{
		return name;
	}
	
	void Destroy();
	
};

