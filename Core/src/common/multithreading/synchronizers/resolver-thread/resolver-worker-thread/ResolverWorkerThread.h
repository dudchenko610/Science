#pragma once

#include "../ResolverThread.h"
#include "../../../notifiable/Notifiable.h"
#include "collections/holding-queue/thread-safe/HoldingQueueSafe.h"

namespace mthreading
{
	class ResolverWorkerThread : public ResolverThread
	{
	protected:
		ResolverWorkerThread();
		virtual ~ResolverWorkerThread();
	public:
		void PushEvent(core::IEvent* e) override;
		
	protected:
		void CheckForEvents();
	private:
		collection::HoldingQueueSafe queue;
	};
}



