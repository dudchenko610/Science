#pragma once

#include <string>
#include <iostream>

namespace avltree 
{
	template<class T>
	class MemBlock;

	template<class T>
	struct Node {

		Node() = default;
		Node(T& value, MemBlock<T>* memBlock);
		Node(Node<T>&) = delete;
		Node(Node<T>&&) = delete;
		Node<T>& operator=(Node<T>&& other);

	
		Node<T>* left;
		Node<T>* right;
		MemBlock<T>* memBlock;

		int bf;
		int height;

		T value;

		std::string GetText()
		{
			return std::to_string(value->value);
		}
	};
}

template<class T>
inline avltree::Node<T>::Node(T& value, MemBlock<T>* memBlock)
	: left(nullptr), right(nullptr), memBlock(memBlock), bf(0), height(0), value(std::move(value))
{
}

template<class T>
inline avltree::Node<T>& avltree::Node<T>::operator=(avltree::Node<T>&& other)
{
	this->left = other.left;
	this->right = other.right;

	this->value = std::move(other.value);

	this->bf = other.bf;
	this->height = other.height;

	this->memBlock = other.memBlock;

	return *this;
}