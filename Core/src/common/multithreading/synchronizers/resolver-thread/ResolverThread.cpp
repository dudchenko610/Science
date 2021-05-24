#include "ResolverThread.h"

#include "../../events/thread-events/ThreadEvents.h"
#include <iostream>

mthreading::ResolverThread::ResolverThread() : isAlive(true), Thread()
{
	std::cout << "Constructor ResolverThread" << std::endl;
}

mthreading::ResolverThread::~ResolverThread()
{
	std::cout << "Destructor ResolverThread" << std::endl;
}

void mthreading::ResolverThread::Stop()
{
	isAlive = false;
}

void mthreading::ResolverThread::OnStarted()
{
	eventMap.SetEventLogic<mthreading::StopThreadEvent>
	(
		[this](mthreading::StopThreadEvent* e)
		{
			std::cout << "ResolverThread STOP ________________" << std::endl;

			Stop();
		}
	);
}

void mthreading::ResolverThread::OnHandleEvent(core::IEvent* e)
{
	this->eventMap.ExecuteEvent(e);
}


