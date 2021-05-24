#pragma once

#include "../avl-tree/AVLTree.h"

namespace collection
{
	template<class T>
	struct BucketHolder
	{
		BucketHolder() = default;
		BucketHolder(int bucketHeightCap, std::function< int(T&) > keyFunc, int key) :
			bucketTree(bucketHeightCap, std::move(keyFunc)),
			key(key)
		{}

		BucketHolder(std::function< int(T&) > keyFunc, int key) :
			bucketTree(std::move(keyFunc)),
			key(key)
		{}

		BucketHolder(BucketHolder<T>&& other)
		{
			this->key = other.key;
//			other.key = 0;
			this->bucketTree = std::move(other.bucketTree);

		}

		BucketHolder<T>& operator=(const BucketHolder<T>& other) = delete;
		BucketHolder<T>& operator=(BucketHolder<T>&& other)
		{
			this->key = other.key;
		//	other.key = 0;
			this->bucketTree = std::move(other.bucketTree);
			
			return *this;
		}

		AVLTree<T> bucketTree;
		int key;
	};

	template<class T>
	class AVLTreeDuplicates : public AVLTree<BucketHolder<T>>
	{
	public:
		AVLTreeDuplicates(
			std::function< int(T&) >&& keyFunc, 
			std::function< int(T&) > bucketKeyFunc
		);
		AVLTreeDuplicates(
			int heightCapacity,
			std::function< int(T&) >&& keyFunc, 
			std::function< int(T&) > bucketKeyFunc
		);
	public:
		bool Insert(T& value);
		bool Insert(T&& value);

		bool Remove(T& value);
		bool Remove(T&& value);
		//using AVLTree<BucketHolder<T>>::Remove;


		T* Get(T& value);
		T* Get(T&& value);
		T* Get(int key);

		T* GetBigger(T& value);
		T* GetBigger(T&& value);
		T* GetBigger(int key);

		T* GetSmaller(T& value);
		T* GetSmaller(T&& value);
		T* GetSmaller(int key);

		int Size();
		int Height();
		bool IsEmpty();

	protected:
		avltree::Node<BucketHolder<T>>* Insert(avltree::Node<BucketHolder<T>>* node, T& value, bool& res);
		avltree::Node<BucketHolder<T>>* Remove(avltree::Node<BucketHolder<T>>* node, T& value, bool& res);

	protected:
		avltree::Node<BucketHolder<T>>* GetNode();
	private:
		std::function< int(T&) > _keyFunc;
		std::function< int(T&) > bucketKeyFunc;
	};

}

template<class T>
collection::AVLTreeDuplicates<T>::AVLTreeDuplicates(
	std::function<int(T&)>&& keyFunc,
	std::function<int(T&)> bucketKeyFunc
) :
	AVLTree<BucketHolder<T>>(
		[](BucketHolder<T>& b)
		{
			return b.key;
		}
	),
	_keyFunc(keyFunc),
	bucketKeyFunc(bucketKeyFunc)
{
}

template<class T>
collection::AVLTreeDuplicates<T>::AVLTreeDuplicates(
	int heightCapacity,
	std::function<int(T&)>&& keyFunc,
	std::function<int(T&)> bucketKeyFunc
) :
	AVLTree<BucketHolder<T>>(
		[](BucketHolder<T>& b)
		{
			return b.key;
		}
	),
	_keyFunc(keyFunc),
	bucketKeyFunc(bucketKeyFunc)
{
}

template<class T>
int collection::AVLTreeDuplicates<T>::Size()
{
	return this->nodeCount;
}

template<class T>
int collection::AVLTreeDuplicates<T>::Height()
{
	return this->root == nullptr ? 0 : this->root->height;
}

template<class T>
bool collection::AVLTreeDuplicates<T>::IsEmpty()
{
	return Size() == 0;
}




template<class T>
bool collection::AVLTreeDuplicates<T>::Insert(T& value)
{

	bool res = false;
	this->root = Insert(this->root, value, res);

	if (res)
		this->nodeCount++;

	return res;
}

template<class T>
bool collection::AVLTreeDuplicates<T>::Insert(T&& value)
{
	bool res = false;
	this->root = Insert(this->root, value, res);

	if (res)
		this->nodeCount++;

	return res;
}

template<class T>
avltree::Node<collection::BucketHolder<T>>* collection::AVLTreeDuplicates<T>::Insert(avltree::Node<collection::BucketHolder<T>>* node, T& value, bool& res)
{
	
	if (node == nullptr)
	{
		res = true;

		avltree::Node<collection::BucketHolder<T>>* n = this->GetNode();

		n->value.key = this->_keyFunc(value);
		n->value.bucketTree.SetKeyFunc(this->bucketKeyFunc);
		n->value.bucketTree.Insert(value);

		return n;
	}

	int cmp = _keyFunc(value) - this->keyFunc(node->value);

	// Insert node in left subtree
	if (cmp < 0)
		node->left = Insert(node->left, value, res);
	// Insert node in right subtree
	else if (cmp > 0)
		node->right = Insert(node->right, value, res);
	else
	{
		res = node->value.bucketTree.Insert(value);
	}

	// Update balance factor and height values
	this->Update(node);

	// Re-balance tree
	return this->Balance(node);

}





template<class T>
bool collection::AVLTreeDuplicates<T>::Remove(T& value)
{
	bool res = false;
	this->root = Remove(this->root, value, res);

	if (res)
		this->nodeCount--;

	return res;
}

template<class T>
bool collection::AVLTreeDuplicates<T>::Remove(T&& value)
{
	bool res = false;
	this->root = Remove(this->root, value, res);

	if (res)
		this->nodeCount--;

	return res;
}


template<class T>
avltree::Node<collection::BucketHolder<T>>* collection::AVLTreeDuplicates<T>::Remove(avltree::Node<collection::BucketHolder<T>>* node, T& value, bool& res)
{
	if (node == nullptr)
		return nullptr;

	int cmp = this->_keyFunc(value) - node->value.key;

	// Dig into left subtree, the value we're looking
	// for is smaller than the current value.
	if (cmp < 0)
	{
		node->left = Remove(node->left, value, res);

		// Dig into right subtree, the value we're looking
		// for is greater than the current value.
	}
	else if (cmp > 0)
	{
		node->right = Remove(node->right, value, res);

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
			int key = this->bucketKeyFunc(value);

			collection::BucketHolder<T>& bucket = node->value;
			res = bucket.bucketTree.Remove(key);

			if (bucket.bucketTree.Size() == 0)
			{
				this->ReleaseNode(node);
				return node->right; // node is lost, should be freed by GC
			}

			return node; 

			// This is the case with only a left subtree or
			// no subtree at all. In this situation just
			// swap the node we wish to remove with its left child.
		}
		else if (node->right == nullptr)
		{
			int key = this->bucketKeyFunc(value);
			
			collection::BucketHolder<T>& bucket = node->value;
			res = bucket.bucketTree.Remove(key);
			

			if (bucket.bucketTree.Size() == 0)
			{
				this->ReleaseNode(node);
				return node->left; // node is lost, should be freed by GC
			}

			return node;

			// When removing a node from a binary tree with two links the
			// successor of the node being removed can either be the largest
			// value in the left subtree or the smallest value in the right
			// subtree. As a heuristic, I will remove from the subtree with
			// the greatest height in hopes that this may help with balancing.
		}
		else
		{	

			int key = this->bucketKeyFunc(value);

			collection::BucketHolder<T>& bucket = node->value;
			res = bucket.bucketTree.Remove(key);
			
			
			
			if (bucket.bucketTree.Size() != 0)
			{
				return node;
			}

			// Choose to remove from left subtree
			if (node->left->height > node->right->height)
			{

				// Swap the value of the successor into the node.
				BucketHolder<T>& successorValue = this->FindMax(node->left);
				node->value = std::move(successorValue);

			//	std::cout << " < successorValue.bucketTree.Size() = " << successorValue.bucketTree.Size() << " successorValue.key = " << successorValue.key << std::endl;

				// Find the largest node in the left subtree.
				node->left = AVLTree<BucketHolder<T>>::Remove(node->left, node->value.key, res); // removes remaining copy !!!

			}
			else
			{

				// Swap the value of the successor into the node.
				BucketHolder<T>& successorValue = this->FindMin(node->right);
				node->value = std::move(successorValue); // shit, or maybe it is ok, it is zbs


			//	std::cout << " < successorValue.bucketTree.Size() = " << successorValue.bucketTree.Size() << " successorValue.key = " << successorValue.key << std::endl;

				// Go into the right subtree and remove the leftmost node we
				// found and swapped data with. This prevents us from having
				// two nodes in our tree with the same value.
				node->right = AVLTree<BucketHolder<T>>::Remove(node->right, node->value.key, res);
			}
		}
	}

	// Update balance factor and height values.
	this->Update(node);

	// Re-balance tree.
	return this->Balance(node);
}

template<class T>
inline avltree::Node<collection::BucketHolder<T>>* collection::AVLTreeDuplicates<T>::GetNode()
{
	if (this->lastRemMemBlock != nullptr)
	{
		avltree::MemBlock<collection::BucketHolder<T>>* tpMm = this->lastRemMemBlock;

		// pop element
		tpMm->removeIndex--;
		avltree::Node<collection::BucketHolder<T>>* newNodeP = tpMm->deleted[tpMm->removeIndex];

		if (tpMm->removeIndex == 0)
		{
			this->lastRemMemBlock = this->lastRemMemBlock->precMemBlck; // O(1) instead of loop O(log(N))
			tpMm->precMemBlck = nullptr;
			// nextMemBlck should be already null
		}

		// manual clearing
		newNodeP->left = nullptr;
		newNodeP->right = nullptr;
		newNodeP->memBlock = tpMm;
		newNodeP->bf = 0;
		newNodeP->height = 0;

		return newNodeP;
	}
	else
	{
		avltree::MemBlock<collection::BucketHolder<T>>& tpMm = this->memBlocks.Last();

		if (tpMm.addIndex == tpMm.size)
			this->AllocateNext();

		avltree::MemBlock<collection::BucketHolder<T>>& topMemBlock = this->memBlocks.Last();
		avltree::Node<collection::BucketHolder<T>>* newNodeP = &topMemBlock.data[topMemBlock.addIndex++];

		// manual clearing
		newNodeP->left = nullptr;
		newNodeP->right = nullptr;
		newNodeP->memBlock = &tpMm;
		newNodeP->bf = 0;
		newNodeP->height = 0;

		return newNodeP;
	}

	return nullptr;
}




template<class T>
T* collection::AVLTreeDuplicates<T>::Get(T& value)
{
	BucketHolder<T>* res = Get(this->root, _keyFunc(value));
	return res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::Get(T&& value)
{
	BucketHolder<T>* res = Get(this->root, _keyFunc(value));
	return res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::Get(int key)
{
	BucketHolder<T>* res = Get(this->root, key);
	return res->bucketTree.GetRootValue();
}




template<class T>
T* collection::AVLTreeDuplicates<T>::GetBigger(T& value)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetBigger(this->root, _keyFunc(value));
	return  res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::GetBigger(T&& value)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetBigger(this->root, _keyFunc(value));
	return  res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::GetBigger(int key)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetBigger(this->root, key);
	return  res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}


template<class T>
T* collection::AVLTreeDuplicates<T>::GetSmaller(T& value)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetSmaller(this->root, _keyFunc(value));
	return res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::GetSmaller(T&& value)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetSmaller(this->root, _keyFunc(value));
	return  res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}

template<class T>
T* collection::AVLTreeDuplicates<T>::GetSmaller(int key)
{
	BucketHolder<T>* res = AVLTree<BucketHolder<T>>::GetSmaller(this->root, key);
	return  res == nullptr ? nullptr : res->bucketTree.GetRootValue();
}