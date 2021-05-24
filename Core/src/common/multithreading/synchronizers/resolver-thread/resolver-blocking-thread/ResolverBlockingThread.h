#pragma once

#include "../../../notifiable/Notifiable.h"
#include "../../../../../events/IEvent.h"

#include "../ResolverThread.h"
#include "collections/holding-queue/HoldingQueue.h"

namespace mthreading
{
	class ResolverBlockingThread : public ResolverThread
	{
	protected:
		ResolverBlockingThread();
		virtual ~ResolverBlockingThread();
	public:
		virtual void PushEvent(core::IEvent* e) override;
	protected:
		void Run();
	protected:
		Notifiable notifiable;
		collection::HoldingQueue queue;
	};
}



