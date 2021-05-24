#include "ResolverWorkerThread.h"
#include <iostream>

mthreading::ResolverWorkerThread::ResolverWorkerThread() 
{
	std::cout << "Constructor ResolverWorkerThread" << std::endl;
}

mthreading::ResolverWorkerThread::~ResolverWorkerThread()
{
	std::cout << "Destructor ResolverWorkerThread" << std::endl;
}

void mthreading::ResolverWorkerThread::PushEvent(core::IEvent* e)
{
	queue.Push(e->GetByteSize(), e);
}


void mthreading::ResolverWorkerThread::CheckForEvents()
{

	if (!queue.IsEmpty())
	{
		char e[1024]; // should be allocated with alloca in future by max event size

		queue.Pop(&e);
		core::IEvent* ev = (core::IEvent*) &e;
		this->OnHandleEvent(ev);
	}
}