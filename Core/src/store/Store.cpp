#include "Store.h"

#include <iostream>

core::Store::Store()
{
	std::cout << "Constructor Store" << std::endl;
}

core::Store::~Store()
{
	std::cout << "Destructor Store" << std::endl;
}

core::Store& core::Store::Get()
{
	std::cout << "Store GET" << std::endl;

	static Store application;
	return application;
}
