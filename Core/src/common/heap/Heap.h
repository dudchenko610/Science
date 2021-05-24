#pragma once

#include "collections/avl-tree/AVLTree.h"
#include "collections/avl-tree-duplicates/AVLTreeDuplicates.h"

#include "memory-structs/FreeMemory.h"

namespace core
{
	class Heap
	{
	public:
		Heap(int size);
		Heap(int size, std::function< int(int) >&& growthFunc);
		~Heap();
	public:
		void Release(void* ptr, int size);
		void Release(int index, int size);
		void* Allocate(int size);
		int IndexOf(void* ptr);
		void* GetData();

		template<class T>
		T* Allocate();

		template<class T>
		int IndexOf(T* ptr);

	private:
		void IncreaseStorage();
	private:
		void* data;
		int size;

		std::function< int(int) > growthFunc;

		collection::AVLTreeDuplicates<FreeMemory> sizeTree;
		collection::AVLTree<FreeMemory> indexTree;
	};
}
template<class T>
T* core::Heap::Allocate()
{
	return reinterpret_cast<T*>(this->Allocate(sizeof(T)));
}

template<class T>
int core::Heap::IndexOf(T* ptr)
{
	int indexOf = this->IndexOf((void*)ptr); // should be in bytes
	return indexOf / sizeof(T);
}


