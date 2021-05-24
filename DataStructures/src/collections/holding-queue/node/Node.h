#pragma once

#include <iostream>

namespace hqueue
{
	class Node
	{
	public:
		Node()
		{
			std::cout << "Holding Queue Node Constructor" << std::endl;
		}
		~Node()
		{
			std::cout << "Holding Queue Node Destructor" << std::endl;
		}
	public:
		Node* prev;
		int size;
	};
}



