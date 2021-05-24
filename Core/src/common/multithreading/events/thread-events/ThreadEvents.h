#pragma once

#include "../../../../events/IEvent.h"
#include "../../thread/Thread.h"

namespace mthreading
{

	class StopThreadEvent : public core::IEvent, public core::Base<StopThreadEvent>
	{
	public:
		StopThreadEvent() : IEvent(id, byteSize) {}
	};


	class ThreadStopedEvent : public core::IEvent, public core::Base<ThreadStopedEvent>
	{
	public:
		ThreadStopedEvent(void* th) : IEvent(id, byteSize), thread(th) {}
	public:
		void* thread;
	};

}