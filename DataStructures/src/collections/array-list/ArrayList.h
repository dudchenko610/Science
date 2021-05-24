#pragma once

#include "node/Node.h"
#include "node/Node.cpp"

using namespace arraylist;

namespace collection 
{
	template<typename T>
	class ArrayList
	{
	public:
		
		ArrayList();
		ArrayList(ArrayList<T>&);
		~ArrayList();
	public:
		void Add(T& data);
		void Add(T&& data);
		T&   Get(int index) const;
		T&   First() const;
		T&   Last() const;
		T    RemoveByIndex(int index);
		bool RemoveByValue(T& data);
		
		template<typename F>
		void ForEach(F functor) 
		{
			Node<T>* current = this->head.next;
			for (int i = 0; i < this->size; i++)
			{
				functor(current->data);
				current = current->next;
			}
		}

		template<typename F>
		void ForEach(F functor) const
		{
			Node<T>* current = this->head.next;
			for (int i = 0; i < this->size; i++)
			{
				functor(current->data);
				current = current->next;
			}
		}

		int  IndexOf(T data);
		int  GetSize() const;
		bool IsEmpty() const;
	public:
		ArrayList<T>& operator=(ArrayList<T>&);
		ArrayList<T>& operator=(ArrayList<T>&&);
//		ArrayList<T>& operator=(const ArrayList<T>&&);
	private:
		T RemoveNode(arraylist::Node<T>* node);
		arraylist::Node<T>* GetNode(int index) const;
	private:
		int size;
		Node<T> head;
		Node<T>* tail;
	};

}

template<class T>
inline collection::ArrayList<T>& collection::ArrayList<T>::operator=(collection::ArrayList<T>&& other)
{
	//this->~ArrayList();

	std::cout << "ArrayList MOVE size = " << this->size << std::endl;


	this->head.next = other.head.next;
	other.head.next = nullptr;

	this->tail = other.tail;
	other.tail = &other.head;

	this->size = other.size;
	other.size = 0;

	return *this;
}

template<class T>
inline collection::ArrayList<T>& collection::ArrayList<T>::operator=(collection::ArrayList<T>& other)
{
	std::cout << "ArrayList COPY size = " << this->size << std::endl;

	this->head.next = other.head.next;
	//other.head.next = nullptr;

	this->tail = other.tail;
	//other.tail = &other.head;

	this->size = other.size;
	//other.size = 0;

	return *this;
}

template<typename T>
collection::ArrayList<T>::ArrayList(collection::ArrayList<T>& other)
{
	std::cout << "ArrayList COPY CONSTRUCTOR = " << this->size << std::endl;

	this->head.next = other.head.next;
	this->tail = other.tail;
	this->size = other.size;
}

template<typename T>
collection::ArrayList<T>::ArrayList()
{
	std::cout << "ArrayList Constructor" << std::endl;


	this->tail = &this->head;

	this->size = 0;
}

template<typename T>
collection::ArrayList<T>::~ArrayList()
{
	std::cout << "ArrayList Destructor" << std::endl;


	Node<T>* current = this->tail;

	if (this->size == 0)
		return;

	do
	{
		current = current->prev;
		delete current->next;
	} while (current != &head);


}

template<typename T>
void collection::ArrayList<T>::Add(T& data)
{

	//std::cout << "~~~~~~~~~ADD " << (int) data << std::endl;

	Node<T>* newElem = new Node<T>();
	newElem->data = data;
	newElem->next = nullptr;
	newElem->prev = this->tail;

	this->tail->next = newElem;
	this->tail = newElem;

	this->size++;
}

template<typename T>
void collection::ArrayList<T>::Add(T&& data)
{
	Node<T>* newElem = new Node<T>();
	newElem->data = std::move(data);
	newElem->next = nullptr;
	newElem->prev = this->tail;

	this->tail->next = newElem;
	this->tail = newElem;

	this->size++;
}

template<typename T>
arraylist::Node<T>* collection::ArrayList<T>::GetNode(int index) const
{

	/*std::cout << "index = " << index << std::endl;*/

	if (index > size - 1)
	{
		return nullptr;
	}



	if (index < size / 2)
	{
		arraylist::Node<T>* current = this->head.next;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current;
	}
	else
	{
		int ind = size - index - 1;

		/*std::cout << "ind " << ind << std::endl;*/

		Node<T>* current = this->tail;
		for (int i = 0; i < ind; i++)
		{
			current = current->prev;
		}

		return current;
	}
}

template<typename T>
T& collection::ArrayList<T>::Get(int index) const
{
	arraylist::Node<T>* node = this->GetNode(index);
	return node->data;
}

template<typename T>
inline T& collection::ArrayList<T>::First() const
{
	return this->head.data;
}

template<typename T>
inline T& collection::ArrayList<T>::Last() const
{
	return this->tail->data;
}

template<typename T>
T collection::ArrayList<T>::RemoveNode(Node<T>* node)
{
	if (node)
	{
		Node<T>* prev = node->prev;
		Node<T>* next = node->next;

		if (node == this->tail)
		{
			prev->next = nullptr;
			this->tail = prev;
		}
		else
		{
			next->prev = prev;
			prev->next = next;
		}

		this->size--;

		T data = node->data;
		delete node;
		return data;

	}

	return 0;
}

template<typename T>
T collection::ArrayList<T>::RemoveByIndex(int index)
{

	if (size == 0)
	{
		return 0;
	}

	Node<T>* node = this->GetNode(index);
	return this->RemoveNode(node);
}

template<typename T>
bool collection::ArrayList<T>::RemoveByValue(T& data)
{
	Node<T>* current = this->head.next;
	for (int i = 0; i < this->size; i++)
	{
		if (current->data == data)
		{
			this->RemoveNode(current);
			return true;
		}
		current = current->next;
	}

	return false;
}

/*template<typename T>
void collection::ArrayList<T>::ForEach(void(*func)(T))
{
	Node<T>* current = this->head->next;
	for (int i = 0; i < this->size; i++)
	{
		func(current->data);
		current = current->next;
	}
}*/

template<typename T>
int collection::ArrayList<T>::GetSize() const
{
	return this->size;
}

template<typename T>
bool collection::ArrayList<T>::IsEmpty() const
{
	return this->size == 0;
}

template<typename T>
int collection::ArrayList<T>::IndexOf(T data)
{

	Node<T>* current = this->head.next;
	for (int i = 0; i < this->size; i++)
	{
		if (current->data == data)
		{
			return i;
		}
		current = current->next;
	}

	return -1;
}

