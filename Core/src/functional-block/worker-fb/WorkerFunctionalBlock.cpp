#include "WorkerFunctionalBlock.h"

#include <iostream>

#include "../../common/multithreading/events/thread-events/ThreadEvents.h"

#include "../../window/Window.h"

core::WorkerFunctionalBlock::WorkerFunctionalBlock(core::Window* wnd) : FunctionalBlock(wnd), ResolverWorkerThread()
{
	std::cout << "Constructor WorkerFunctionalBlock" << std::endl;
}

core::WorkerFunctionalBlock::~WorkerFunctionalBlock()
{
	std::cout << "Destructor WorkerFunctionalBlock" << std::endl;
}

void core::WorkerFunctionalBlock::Run()
{
	std::cout << "Run WorkerFunctionalBlock" << std::endl;

	OnStarted();

	while (isAlive)
	{
		OnUpdate();
		CheckForEvents();
	}

	std::cout << "FINISH WorkerFunctionalBlock" << std::endl;

}


void core::WorkerFunctionalBlock::OnStoped()
{
	mthreading::ThreadStopedEvent ev(this);
	this->wnd->PushEvent( &ev );

	std::cout << "OnStoped WorkerFunctionalBlock" << std::endl;
}

