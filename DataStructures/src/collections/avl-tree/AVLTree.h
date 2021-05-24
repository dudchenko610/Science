#pragma once

#include <iostream>
#include <math.h>
#include <functional>

#include "MemBlock.h"


#include "../array-list/ArrayList.h"

namespace collection
{
	
	template<class T>
	class AVLTree
	{
	public:
		AVLTree(std::function< int(T&) >&& keyFunc);
		AVLTree(int heightCapacity, std::function< int(T&) >&& keyFunc);
		~AVLTree();
	public:
		AVLTree();

	public:
		bool Insert(T& value);
		bool Insert(T&& value);

		bool Remove(T& value);
		bool Remove(T&& value);
		bool Remove(int key);


		bool Contains(T& value);
		bool Contains(int key);

		T* Get(T& value);
		T* Get(T&& value);
		T* Get(int key);

		T* GetBigger(T& value);
		T* GetBigger(T&& value);
		T* GetBigger(int key);

		T* GetSmaller(T& value);
		T* GetSmaller(T&& value);
		T* GetSmaller(int key);

		T* GetRootValue();

		int Size();
		int AllocatedSize();
		int Height();
		bool IsEmpty();

	public:
		AVLTree<T>& operator=(AVLTree<T>&) = delete;
		AVLTree<T>& operator=(AVLTree<T>&&);
	//	AVLTree<T>& operator=(const AVLTree<T>&&);

	protected:
		virtual avltree::Node<T>* Insert(avltree::Node<T>* node, T& value, bool& res);
		virtual avltree::Node<T>* Remove(avltree::Node<T>* node, int key, bool& res);

		virtual T* Get(avltree::Node<T>* node, int key);
		virtual T* GetBigger(avltree::Node<T>* node, int key);
		virtual T* GetSmaller(avltree::Node<T>* node, int key);

		bool Contains(avltree::Node<T>* node, int key);

		void Update(avltree::Node<T>* node);
		avltree::Node<T>* Balance(avltree::Node<T>* node);

	public:
		void SetKeyFunc(std::function< int(T&) >& keyFunc);

	protected:
		T& FindMin(avltree::Node<T>* node);
		T& FindMax(avltree::Node<T>* node);

	protected:
		avltree::Node<T>* LeftLeftCase(avltree::Node<T>* node);
		avltree::Node<T>* LeftRightCase(avltree::Node<T>* node);
		avltree::Node<T>* RightRightCase(avltree::Node<T>* node);
		avltree::Node<T>* RightLeftCase(avltree::Node<T>* node);

		avltree::Node<T>* LeftRotation(avltree::Node<T>* node);
		avltree::Node<T>* RightRotation(avltree::Node<T>* node);


	protected:
		void AllocateNext(); // linear time complexity
		avltree::Node<T>* GetNode(T& value);
		void ReleaseNode(avltree::Node<T>* node);

	public:
		avltree::Node<T>* root;
	protected:

		collection::ArrayList<avltree::MemBlock<T>> memBlocks;
		avltree::MemBlock<T>* lastRemMemBlock;

		std::function< int(T&) > keyFunc;

		int nodeCount;
		int allocatedHeight;
		int allocatedSize;

	};
}

// we create a new memblock only after preceding one filled up

template<class T>
collection::AVLTree<T>::AVLTree(std::function< int(T&) >&& keyFunc) :
	root(nullptr),
	nodeCount(0),
	allocatedHeight(0),
	lastRemMemBlock(nullptr),
	keyFunc(std::move(keyFunc))
{
	std::cout << "AVLTree Constructor" << std::endl;
	// allocate memory
	AllocateNext();
}


template<class T>
collection::AVLTree<T>::AVLTree(int heightCapacity, std::function< int(T&) >&& keyFunc) :
	root(nullptr),
	nodeCount(0),
	allocatedHeight(heightCapacity),
	lastRemMemBlock(nullptr),
	keyFunc(std::move(keyFunc))
{
	//std::cout << "AVLTree Constructor" << std::endl;

	AllocateNext();
}

template<class T>
collection::AVLTree<T>::AVLTree() :
	root(nullptr),
	nodeCount(0),
	allocatedHeight(0),
	lastRemMemBlock(nullptr)
{
	AllocateNext();
//	std::cout << "AVLTree Constructor" << std::endl;

}


template<class T>
collection::AVLTree<T>::~AVLTree()
{
//	std::cout << "AVLTree Destructor" << std::endl;
}

template<class T>
inline collection::AVLTree<T>& collection::AVLTree<T>::operator=(collection::AVLTree<T>&& other)
{
	//std::cout << "AVLTree MOVE, swap behavior" << std::endl;

	auto root = this->root;
	this->root = other.root;
	other.root = root;
	
	auto lastRemMemBlock = this->lastRemMemBlock;
	this->lastRemMemBlock = other.lastRemMemBlock;
	other.lastRemMemBlock = lastRemMemBlock;

	auto nodeCount = this->nodeCount;
	this->nodeCount = other.nodeCount;
	other.nodeCount = nodeCount;

	auto allocatedHeight = this->allocatedHeight;
	this->allocatedHeight = other.allocatedHeight;
	other.allocatedHeight = allocatedHeight;

	auto allocatedSize = this->allocatedSize;
	this->allocatedSize = other.allocatedSize;
	other.allocatedSize = allocatedSize;
	
//	std::cout << "SHOULD BE DESTRUCTOR" << std::endl;

	auto memBlocks = this->memBlocks;
	this->memBlocks = std::move(other.memBlocks);
	other.memBlocks = std::move(memBlocks);

	this->keyFunc = other.keyFunc;

	return *this;
}

template<class T>
void collection::AVLTree<T>::SetKeyFunc(std::function< int(T&) >& keyFunc)
{
	this->keyFunc = keyFunc;
}

template<class T>
void collection::AVLTree<T>::AllocateNext()
{
	this->allocatedSize = (1 << (this->allocatedHeight + 1)) - 1; // 2^(h + 1) - 1
	int levelSize = 1 << this->allocatedHeight;
	this->allocatedHeight += 1;

	//std::cout << "memBlocks.Add(avltree::MemBlock<T>(levelSize));" << std::endl;

	memBlocks.Add(avltree::MemBlock<T>(levelSize)); // should be checked
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::GetNode(T& value)
{

	if (memBlocks.GetSize() == 0)
	{
		AllocateNext();
	}

	if (this->lastRemMemBlock != nullptr)
	{
		avltree::MemBlock<T>* tpMm = this->lastRemMemBlock;
		
		// pop element
		tpMm->removeIndex--;
		avltree::Node<T>* newNodeP = tpMm->deleted[tpMm->removeIndex];

		if (tpMm->removeIndex == 0)
		{
			this->lastRemMemBlock = this->lastRemMemBlock->precMemBlck; // O(1) instead of loop O(log(N))
			tpMm->precMemBlck = nullptr;
			// nextMemBlck should be already null
		}

		*newNodeP = avltree::Node<T>(value, tpMm);
		return newNodeP;
	}
	else
	{
		avltree::MemBlock<T>& tpMm = this->memBlocks.Last();

		if (tpMm.addIndex == tpMm.size)
			AllocateNext();

		avltree::MemBlock<T>& topMemBlock = this->memBlocks.Last();
		avltree::Node<T>* newNodeP = &topMemBlock.data[topMemBlock.addIndex++];

		*newNodeP = avltree::Node<T>(value, &topMemBlock);
		return newNodeP;
	}
	
}

template<class T>
void collection::AVLTree<T>::ReleaseNode(avltree::Node<T>* node)
{
	node->memBlock->deleted[node->memBlock->removeIndex++] = node;
	
	if (this->lastRemMemBlock == nullptr)
	{
		this->lastRemMemBlock = node->memBlock;
	} 
	// (this->lastRemMemBlock == node->memBlock) => removing from last memBlock, it is totally ok, do nothing
	else if (this->lastRemMemBlock != node->memBlock)
	{
		// we are adding block on top of other
		if (node->memBlock->nextMemBlck == nullptr)
		{
			avltree::MemBlock<T>* lastRMB = this->lastRemMemBlock;

			this->lastRemMemBlock = node->memBlock;
			lastRMB->nextMemBlck = node->memBlock;
			node->memBlock->precMemBlck = lastRMB;
		}
		// we are adding block in front of chain
		else
		{
			// extract block from chain

			if (node->memBlock->precMemBlck != nullptr)
			{
				node->memBlock->precMemBlck->nextMemBlck = node->memBlock->nextMemBlck;
				node->memBlock->precMemBlck = nullptr;
			}

			node->memBlock->nextMemBlck->precMemBlck = node->memBlock->precMemBlck;
			node->memBlock->nextMemBlck = nullptr;

			// connect just on top
			avltree::MemBlock<T>* lastRMB = this->lastRemMemBlock;
			this->lastRemMemBlock = node->memBlock;
			lastRMB->nextMemBlck = node->memBlock;
			node->memBlock->precMemBlck = lastRMB;

		}
	}
}


template<class T>
int collection::AVLTree<T>::Size()
{
	return nodeCount;
}

template<class T>
int collection::AVLTree<T>::AllocatedSize()
{
	return allocatedSize;
}

template<class T>
int collection::AVLTree<T>::Height()
{
//	std::cout << "AVLTree Height" << std::endl;
	return root == nullptr ? 0 : root->height;
}

template<class T>
bool collection::AVLTree<T>::IsEmpty()
{
	return Size() == 0;
}



template<class T>
bool collection::AVLTree<T>::Insert(T& value)
{

	bool res = false;
	root = Insert(root, value, res);

	if (res)
		nodeCount++;

	return res;
}

template<class T>
bool collection::AVLTree<T>::Insert(T&& value)
{
	bool res = false;
	root = Insert(root, value, res);

	if (res)
		nodeCount++;

	return res;
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::Insert(avltree::Node<T>* node, T& value, bool& res)
{
	if (node == nullptr)
	{
		res = true;
		// move semantics should be explored // it is done !!!! 18.04.2021 / 21:54
		avltree::Node<T>* n = GetNode(value);
		return n;
	}

	int cmp = keyFunc(value) - keyFunc(node->value);


	// Insert node in left subtree
	if (cmp < 0)
		node->left = Insert(node->left, value, res);
	// Insert node in right subtree
	else if (cmp > 0)
		node->right = Insert(node->right, value, res);

	// Update balance factor and height values
	Update(node);

	// Re-balance tree
	return Balance(node);
}


template<class T>
bool collection::AVLTree<T>::Remove(T& value)
{
	bool res = false;
	root = Remove(root, keyFunc(value), res);

	if (res)
		nodeCount--;
	
	return res;
}

template<class T>
bool collection::AVLTree<T>::Remove(T&& value)
{
	bool res = false;
	root = Remove(root, keyFunc(value), res);

	if (res)
		nodeCount--;

	return res;
}

template<class T>
bool collection::AVLTree<T>::Remove(int key)
{
	bool res = false;
	root = Remove(root, key, res);

	if (res)
		nodeCount--;

	return res;
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::Remove(avltree::Node<T>* node, int key, bool& res)
{
	if (node == nullptr) 
	{
		return nullptr;
	}

	int cmp = key - keyFunc(node->value);

	// Dig into left subtree, the value we're looking
	// for is smaller than the current value.
	if (cmp < 0) 
	{
		node->left = Remove(node->left, key, res);

		// Dig into right subtree, the value we're looking
		// for is greater than the current value.
	}
	else if (cmp > 0) 
	{
		node->right = Remove(node->right, key, res);

		// Found the node we wish to remove.
	}
	else 
	{
		// This is the case with only a right subtree or no subtree at all.
		// In this situation just swap the node we wish to remove
		// with its right child.
		if (node->left == nullptr) 
		{
////////////// node RELEASE

			res = true;
			ReleaseNode(node);
			return node->right; // node is lost, should be freed by GC

			// This is the case with only a left subtree or
			// no subtree at all. In this situation just
			// swap the node we wish to remove with its left child.
		}
		else if (node->right == nullptr) 
		{
			res = true;
			ReleaseNode(node);
			return node->left; // node is lost, should be freed by GC

			// When removing a node from a binary tree with two links the
			// successor of the node being removed can either be the largest
			// value in the left subtree or the smallest value in the right
			// subtree. As a heuristic, I will remove from the subtree with
			// the greatest height in hopes that this may help with balancing.
		}
		else 
		{
			// Choose to remove from left subtree
			if (node->left->height > node->right->height)
			{
				// Swap the value of the successor into the node.
				T& successorValue = FindMax(node->left);
				node->value = std::move(successorValue);

				// Find the largest node in the left subtree.
				node->left = Remove(node->left, keyFunc(successorValue), res); // removes remaining copy !!!

			}
			else 
			{
				// Swap the value of the successor into the node.
				T& successorValue = FindMin(node->right);
				node->value = std::move(successorValue);

				// Go into the right subtree and remove the leftmost node we
				// found and swapped data with. This prevents us from having
				// two nodes in our tree with the same value.
				node->right = Remove(node->right, keyFunc(successorValue), res);
			}
		}
	}

	// Update balance factor and height values.
	Update(node);

	// Re-balance tree.
	return Balance(node);
}



template<class T>
T* collection::AVLTree<T>::Get(T& value)
{
	return Get(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::Get(T&& value)
{
	return Get(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::Get(int key)
{
	return Get(root, key);
}

template<class T>
T* collection::AVLTree<T>::Get(avltree::Node<T>* node, int key)
{
	if (node == nullptr)
		return nullptr;

	int cmp = key - keyFunc(node->value);;

	if (cmp < 0)
		return Get(node->left, key);

	if (cmp > 0)
		return Get(node->right, key);

	return &node->value;
}



template<class T>
bool collection::AVLTree<T>::Contains(T& value)
{
	return Contains(root, keyFunc(value));
}

template<class T>
bool collection::AVLTree<T>::Contains(int key)
{
	return Contains(root, key);
}


template<class T>
bool collection::AVLTree<T>::Contains(avltree::Node<T>* node, int key) 
{
	if (node == nullptr)
		return false;

	int cmp = key - keyFunc(node->value);

	if (cmp < 0)
		return Contains(node->left, key);

	if (cmp > 0) 
		return Contains(node->right, key);

	return true;
}




template<class T>
T* collection::AVLTree<T>::GetRootValue()
{
	return root == nullptr ? nullptr : &root->value;
}



template<class T>
T* collection::AVLTree<T>::GetBigger(T& value) 
{
	return GetBigger(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::GetBigger(T&& value)
{
	return GetBigger(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::GetBigger(int key)
{
	return GetBigger(root, key);
}



template<class T>
T* collection::AVLTree<T>::GetBigger(avltree::Node<T>* node, int key)
{
	if (node == nullptr)
		return nullptr;

	int cmp = key - keyFunc(node->value);

	T* data = nullptr;

	if (cmp < 0)
		data = GetBigger(node->left, key);
	else if (cmp > 0)
		data = GetBigger(node->right, key);
	else 
		return &node->value;


	if (data == nullptr && cmp < 0)
		return &node->value;

	return data;
}

template<class T>
T* collection::AVLTree<T>::GetSmaller(T& value)
{
	return GetSmaller(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::GetSmaller(T&& value)
{
	return GetSmaller(root, keyFunc(value));
}

template<class T>
T* collection::AVLTree<T>::GetSmaller(int key)
{
	return GetSmaller(root, key);
}

template<class T>
T* collection::AVLTree<T>::GetSmaller(avltree::Node<T>* node, int key)
{
	if (node == nullptr)
		return nullptr;

	int cmp = key - keyFunc(node->value);;

	T* data = nullptr;

	if (cmp < 0)
		data = GetSmaller(node->left, key);
	else if (cmp > 0)
		data = GetSmaller(node->right, key);
	else
		return &node->value;


	if (data == nullptr && cmp > 0)
		return &node->value;

	return data;
}



template<class T>
void collection::AVLTree<T>::Update(avltree::Node<T>* node)
{
	int leftNodeHeight = (node->left == nullptr) ? -1 : node->left->height;
	int rightNodeHeight = (node->right == nullptr) ? -1 : node->right->height;

	// Update this node's height
	node->height = 1 + std::max(leftNodeHeight, rightNodeHeight);

	// Update balance factor
	node->bf = rightNodeHeight - leftNodeHeight;
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::Balance(avltree::Node<T>* node)
{
	// Left heavy subtree
	if (node->bf == -2) 
	{
		// Left-Left case
		if (node->left->bf <= 0)
		{
			return LeftLeftCase(node);
		}
		// Left-Right case
		else
		{
			return LeftRightCase(node);
		}
	}
	else if (node->bf == +2)
	{
		// Right-Right case
		if (node->right->bf >= 0) 
		{
			return RightRightCase(node);
		}
		// Right-Left case
		else 
		{
			return RightLeftCase(node);
		}
	}

	// Node either has a balance factor of 0, +1 or -1 which is fine
	return node;
}




template<class T>
avltree::Node<T>* collection::AVLTree<T>::LeftLeftCase(avltree::Node<T>* node)
{
	return RightRotation(node);
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::LeftRightCase(avltree::Node<T>* node)
{
	node->left = LeftRotation(node->left);
	return LeftLeftCase(node);
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::RightRightCase(avltree::Node<T>* node)
{
	return LeftRotation(node);
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::RightLeftCase(avltree::Node<T>* node)
{
	node->right = RightRotation(node->right);
	return RightRightCase(node);
}




template<class T>
avltree::Node<T>* collection::AVLTree<T>::RightRotation(avltree::Node<T>* node)
{
	avltree::Node<T>* newParent = node->left;
	node->left = newParent->right;
	newParent->right = node;

	Update(node);
	Update(newParent);

	return newParent;
}

template<class T>
avltree::Node<T>* collection::AVLTree<T>::LeftRotation(avltree::Node<T>* node)
{
	avltree::Node<T>* newParent = node->right;
	node->right = newParent->left;
	newParent->left = node;

	Update(node);
	Update(newParent);

	return newParent;
}


// Helper method to find the rightmost node (which has the largest value)
template<class T>
T& collection::AVLTree<T>::FindMax(avltree::Node<T>* node)
{
	while (node->right != nullptr) node = node->right;
	return node->value;
}

// Helper method to find the leftmost node (which has the smallest value)
template<class T>
T& collection::AVLTree<T>::FindMin(avltree::Node<T>* node)
{
	while (node->left != nullptr) node = node->left;
	return node->value;
}


