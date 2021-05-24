#include "Heap.h"

core::Heap::Heap(int size) :
	Heap(size, 
		[](int oldSize)
		{
			return oldSize * 2;
		}
	)
{
}

core::Heap::Heap(int size, std::function<int(int)>&& growthFunc) :
    growthFunc(growthFunc),
	size(size),
	
	sizeTree(
		[](FreeMemory& fm)
		{
			return fm.size;
		},
		[](FreeMemory& fm)
		{
			return fm.index;
		}
	),

	indexTree(
		[](FreeMemory& fm)
		{
			return fm.index;
		}
	),
	data(new void*[size])

{
	std::cout << "HEAP CONSTRUCTOR size = " << size << std::endl;
	
	sizeTree.Insert({0, size });
	indexTree.Insert({0, size });

}

core::Heap::~Heap()
{
	delete[] data;
}

void core::Heap::Release(void* ptr, int size)
{
	int index = (int) ((int)ptr - (int)this->data);
	if (index <= 0 || index > size)
		return;

	this->Release(index, size);
}

void core::Heap::Release(int index, int size)
{
	FreeMemory clearedMemBl(index, size);

	FreeMemory* beforeMemBl = indexTree.GetSmaller(index);
	if (beforeMemBl != nullptr && beforeMemBl->index + beforeMemBl->size == index)
	{
		clearedMemBl.index -= beforeMemBl->size;
		clearedMemBl.size += beforeMemBl->size;

		indexTree.Remove(index);
		sizeTree.Remove(*beforeMemBl);
	}

	FreeMemory* afterMemBl = indexTree.Get(index + size);
	if (afterMemBl != nullptr)
	{
		clearedMemBl.size += afterMemBl->size;
		indexTree.Remove(*afterMemBl);
		sizeTree.Remove(*afterMemBl);
	}

	indexTree.Insert(clearedMemBl);
	sizeTree.Insert(clearedMemBl);

	// O(8*log(n)) withoul alloc in advance

	// problem: avl tree should support duplicates. Solved one day later

}

void* core::Heap::Allocate(int size)
{

	std::cout << "void* core::Heap::Allocate(int size) = " << size << std::endl;


	FreeMemory* memBl = sizeTree.GetBigger(size);

	std::cout << (memBl == nullptr) << std::endl;

	if (memBl != nullptr)
	{
		std::cout << "index = " << memBl->index << std::endl;

	}


	while (memBl == nullptr) // if wrong growth function, it is infinite
	{
		IncreaseStorage(); // linear behavior O(n) while copying
		memBl = sizeTree.GetBigger(size);
	}

	sizeTree.Remove(*memBl);
	indexTree.Remove(*memBl);

	if (memBl->size - size > 0)
	{
		FreeMemory rest(memBl->index + size, memBl->size - size);
		sizeTree.Insert(rest);
		indexTree.Insert(rest);

		std::cout << "insert = " << rest.index << " " << rest.size << std::endl;

	}
	

	// summurry O( 6 * log( n ) )

    return (void*) ((unsigned int) data + memBl->index);
}

int core::Heap::IndexOf(void* ptr)
{
	int index = (int)((int)ptr - (int)this->data);
	if (index <= 0 || index > size)
		return -1;

	return index;
}

void* core::Heap::GetData()
{
	return data;
}

void core::Heap::IncreaseStorage()
{
	std::cout << "IncreaseStorage" << std::endl;


	// not just simple, trees must be affected
	void* oldData = this->data;
	int newSize = growthFunc(size);

	if (newSize <= size)
	{
		newSize = 2 * size;
	}

	FreeMemory clearedMemBl(size, size);

	FreeMemory* memBl = indexTree.GetSmaller(size); // get last index from index tree
	if (/*memBl != nullptr && */(memBl->index + memBl->size) == size) // it is free block in the end of data array, never should be nullptr
	{
		indexTree.Remove(*memBl);
		sizeTree.Remove(*memBl);

		clearedMemBl.index = memBl->index;
		clearedMemBl.size += size - memBl->index;
	}

	indexTree.Insert(clearedMemBl);
	sizeTree.Insert(clearedMemBl);


	this->data = new void*[newSize];
	memcpy(this->data, oldData, size);

	this->size = newSize;
	delete[] oldData;
}
