#pragma once

#include "Node.h"

namespace avltree
{
	template<class T>
	class MemBlock
	{
//	friend class Node<T>;
	public:
		MemBlock();
		MemBlock(int size);
		MemBlock(MemBlock& memBlock) = delete;
		MemBlock(MemBlock&& memBlock);

		MemBlock& operator=(MemBlock&& memBlock);

		~MemBlock();
//	private:
		Node<T>* data;
		Node<T>** deleted;

		int removeIndex;
		int addIndex;
		int size;

		MemBlock<T>* precMemBlck;
		MemBlock<T>* nextMemBlck;

	};
}


template<class T>
avltree::MemBlock<T>::MemBlock() :
	size(0), removeIndex(0), addIndex(0),
	data(nullptr), deleted(nullptr),
	precMemBlck(nullptr), nextMemBlck(nullptr)
{
	//std::cout << "MemBlock Empty Constructor" << std::endl;
}

template<class T>
avltree::MemBlock<T>::MemBlock(int size) :
	size(size), removeIndex(0), addIndex(0),
	precMemBlck(nullptr), nextMemBlck(nullptr)
{
	//std::cout << "MemBlock Working Constructor" << std::endl;

	this->data = new Node<T>[size];
	this->deleted = new Node<T>*[size];
}

template<class T>
avltree::MemBlock<T>::MemBlock(avltree::MemBlock<T>&& memBlock)
{
	//std::cout << "MemBlock Move Constructor" << std::endl;
	
	this->data = memBlock.data;
	this->deleted = memBlock.deleted;

	this->removeIndex = memBlock.removeIndex;
	this->addIndex = memBlock.addIndex;
	this->size = memBlock.size;

	this->precMemBlck = memBlock.precMemBlck;
	this->nextMemBlck = memBlock.nextMemBlck;

	memBlock.precMemBlck = nullptr;
	memBlock.nextMemBlck = nullptr;

	memBlock.data = nullptr; 
	memBlock.deleted = nullptr;
}

template<class T>
inline avltree::MemBlock<T>& avltree::MemBlock<T>::operator=(MemBlock&& memBlock)
{
	//std::cout << "MemBlock operator=" << std::endl;

	if (this != &memBlock)
	{
		delete[] this->data; // usually it is null in terms of use of this class
		delete[] this->deleted;

		this->data = memBlock.data;
		this->deleted = memBlock.deleted;

		this->removeIndex = memBlock.removeIndex;
		this->addIndex = memBlock.addIndex;
		this->size = memBlock.size;

		this->precMemBlck = memBlock.precMemBlck;
		this->nextMemBlck = memBlock.nextMemBlck;

		memBlock.data = nullptr;
		memBlock.deleted = nullptr;

		memBlock.precMemBlck = nullptr;
		memBlock.nextMemBlck = nullptr;
	}

	return *this;
}

template<class T>
avltree::MemBlock<T>::~MemBlock()
{
	//std::cout << "MemBlock DESTRUCTOR" << std::endl;

	delete[] this->data;
	delete[] this->deleted;
}