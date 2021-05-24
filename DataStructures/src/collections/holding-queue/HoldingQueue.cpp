#include "HoldingQueue.h"


collection::HoldingQueue::HoldingQueue() : size(0), last(nullptr)
{
	std::cout << "Holding Queue Constructor" << std::endl;

	this->first.prev = nullptr;
	this->last = &first;
}

collection::HoldingQueue::~HoldingQueue()
{
	std::cout << "Holding Queue Destructor" << std::endl;

	hqueue::Node* node = this->last;
	hqueue::Node* todel = nullptr;
	hqueue::Node* frst = &this->first;

	while (node != frst)
	{
		todel = node;
		node = node->prev;
		char* ptr = (char*)todel; // smth strange, but should be ok :)
		delete ptr;
	}
}

void collection::HoldingQueue::Clean()
{
	hqueue::Node* node = this->last;
	hqueue::Node* todel = nullptr;
	hqueue::Node* frst = &this->first;

	while (node != frst)
	{
		todel = node;
		node = node->prev;
		char* ptr = (char*)todel; // smth strange, but should be ok :)
		delete ptr;
	}

	this->size = 0;
}

void collection::HoldingQueue::Push(int typeSize, void* data)
{

	//std::cout << "Push typeSize: " << typeSize << std::endl;

	char* _node = new char[typeSize + 8];                 // 8 = 4 + 4 : 4 = prev, 4 = size;

	hqueue::Node* node = (hqueue::Node*) _node;
	memcpy(_node + 8, data, typeSize);

	node->size = typeSize;
	node->prev = this->last;
	this->last = node;
	this->size++;
}

void collection::HoldingQueue::Pop(void* data)
{
	if (this->size == 0)
	{
		return;
	}

	hqueue::Node* node = this->last;
	char* _node = (char*) node;

	this->last = node->prev;

	memcpy(data, _node + 8, node->size);

	delete _node; // smth strange but should be working

	this->size--;
}

int collection::HoldingQueue::GetSize() const
{
	return this->size;
}


bool collection::HoldingQueue::IsEmpty() const
{
	return this->size == 0;
}
