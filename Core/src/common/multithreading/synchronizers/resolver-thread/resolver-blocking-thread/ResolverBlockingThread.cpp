#include "ResolverBlockingThread.h"

#include <iostream>

mthreading::ResolverBlockingThread::ResolverBlockingThread(): ResolverThread()
{
	std::cout << "Constructor ResolverBlockingThread" << std::endl;
}

mthreading::ResolverBlockingThread::~ResolverBlockingThread()
{
	std::cout << "Destructor ResolverBlockingThread" << std::endl;
}

void mthreading::ResolverBlockingThread::PushEvent(core::IEvent* e)
{
	notifiable.DoSync([this, &e]() {
		queue.Push(e->GetByteSize(), e);
	});

	notifiable.NotifyOne();
}

void mthreading::ResolverBlockingThread::Run()
{
	std::cout << "Run ResolverBlockingThread" << std::endl;

	OnStarted();

	while (isAlive)
	{
		char e[1024]; // should be allocated with alloca in future by max event size

		notifiable.Wait(
			[this, &e]() { return queue.GetSize() != 0 || !isAlive; },
			[this, &e]() // critical section
			{
				queue.Pop(&e);
			}
		);
		
		core::IEvent* ev = (core::IEvent*) & e;
		OnHandleEvent(ev);
	}

	OnStoped();

}