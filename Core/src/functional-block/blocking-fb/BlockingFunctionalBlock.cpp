#include "BlockingFunctionalBlock.h"

#include <iostream>

#include "../../common/multithreading/events/thread-events/ThreadEvents.h"

#include "../../window/Window.h"

core::BlockingFunctionalBlock::BlockingFunctionalBlock(core::Window* wnd) : ResolverBlockingThread(), FunctionalBlock(wnd)
{
	std::cout << "Constructor BlockingFunctionalBlock" << std::endl;
}

core::BlockingFunctionalBlock::~BlockingFunctionalBlock()
{
	std::cout << "Destructor BlockingFunctionalBlock" << std::endl;
}

void core::BlockingFunctionalBlock::PushEvent(core::IEvent* e)
{
	ResolverBlockingThread::PushEvent(e);
}

void core::BlockingFunctionalBlock::OnStoped()
{
	mthreading::ThreadStopedEvent ev((core::FunctionalBlock*) this);
	this->wnd->PushEvent( &ev );
}


