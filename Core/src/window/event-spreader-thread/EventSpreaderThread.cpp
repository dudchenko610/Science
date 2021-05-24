#include "EventSpreaderThread.h"

#include <iostream>
#include "../Window.h"

core::EventSpreaderThread::EventSpreaderThread(core::Window* wnd) 
	: 
	wnd(wnd),
	functionalBlocks(&wnd->functionalBlocks),
	ResolverBlockingThread()
{
	std::cout << "EventSpreaderThread Constructor" << std::endl;
}

core::EventSpreaderThread::~EventSpreaderThread()
{
	std::cout << "EventSpreaderThread Destructor" << std::endl;
}

void core::EventSpreaderThread::PushEvent(core::IEvent* e)
{
	functionalBlocks->ForEach
	(
		[&e](core::FunctionalBlock* fb)
		{
			fb->PrepareEventInWindowThread(e);
		}
	);

	ResolverBlockingThread::PushEvent(e);
}

void core::EventSpreaderThread::OnHandleEvent(core::IEvent* e)
{
	bool toContinue = true;

	functionalBlocks->ForEach
	(
		[&e, &toContinue](core::FunctionalBlock* fb)
		{
			if (toContinue && fb->CheckEventInSpreaderThread(e))
			{
				fb->PushEvent(e);
				toContinue = false;
				// interrupt iterating
			}
		}
	);
	
	
	ResolverBlockingThread::OnHandleEvent(e);
}


void core::EventSpreaderThread::OnStarted()
{
	ResolverBlockingThread::OnStarted();
}

void core::EventSpreaderThread::OnStoped()
{
	mthreading::ThreadStopedEvent ev(this);
	this->wnd->PushEvent( &ev );
}
