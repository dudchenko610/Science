#pragma once

#include "../../thread/Thread.h"
#include "../../../../events/IEvent.h"
#include "../../../../events/EventMapVoid.h"


namespace mthreading
{
	class ResolverThread : public Thread
	{
	protected:
		ResolverThread();
		virtual ~ResolverThread();
	public:
		virtual void PushEvent(core::IEvent* e) = 0;
	protected:
		virtual void Run() = 0;
		virtual void OnHandleEvent(core::IEvent* e);
		virtual void OnStarted();
		virtual void OnStoped() = 0;
		
		void Stop();
	protected:
		bool isAlive;
		core::EventMapVoid eventMap;
	};
}


