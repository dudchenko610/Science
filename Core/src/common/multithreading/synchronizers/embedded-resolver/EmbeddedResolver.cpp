#include "EmbeddedResolver.h"

#include <iostream>

mthreading::EmbeddedResolver::EmbeddedResolver() : isAlive(true)
{
	std::cout << "Constructor EmbeddedResolver" << std::endl;
}

mthreading::EmbeddedResolver::~EmbeddedResolver()
{
	std::cout << "Destructor EmbeddedResolver" << std::endl;
}

void mthreading::EmbeddedResolver::PushEvent(core::IEvent* e)
{
	std::cout << "EmbeddedResolver PushEvent" << std::endl;

	notifiable.DoSync([this, &e]() {
		queue.Push(e->GetByteSize(), e);
	});

	notifiable.NotifyOne();
}


void mthreading::EmbeddedResolver::Stop()
{
	notifiable.DoSync([this]() {
		isAlive = false;
	});

	notifiable.NotifyOne();
}


void mthreading::EmbeddedResolver::Go()
{
	std::cout << "Run ResolverBlockingThread" << std::endl;

	this->OnStarted();

	char e[1024]; // should be allocated with alloca in future by max event size

	while (isAlive)
	{
		notifiable.Wait(
			[this, &e]() { return queue.GetSize() != 0 || !isAlive; },
			[this, &e]() // critical section
			{
				queue.Pop(&e);
			}
		);

		core::IEvent* ev = (core::IEvent*) &e;
		OnHandleEvent(ev);
	}

	this->OnStoped();
}

void mthreading::EmbeddedResolver::OnHandleEvent(core::IEvent* e)
{
	this->eventMap.ExecuteEvent(e);
}


