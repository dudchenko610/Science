#pragma once

#include "node/Node.h"

#include <iostream>


namespace collection
{
	class HoldingQueue
	{
	public:
		HoldingQueue();
		~HoldingQueue();
	public:
		void Push(int typeSize, void* data);
		void Pop(void* data);

		void Clean();

		int GetSize() const;
		bool IsEmpty() const;
	private:
		hqueue::Node first;
		hqueue::Node* last;
		int size;
	};
}