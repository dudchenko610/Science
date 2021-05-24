#pragma once

#include "../../notifiable/Notifiable.h"

#include "../../../../events/EventFactory.h"
#include "../../../../events/IEvent.h"
#include "../../../../events/EventMapVoid.h"

#include "collections/holding-queue/HoldingQueue.h"

namespace mthreading
{
	class EmbeddedResolver
	{
	public:
		EmbeddedResolver();
		virtual ~EmbeddedResolver();
	public:
		
		void PushEvent(core::IEvent* e);

		virtual void OnStarted() = 0;
		virtual void OnStoped() = 0;

		void Stop();
	protected:
		void Go();
		virtual void OnHandleEvent(core::IEvent* e);
	private:
		bool isAlive;
		Notifiable notifiable;
		collection::HoldingQueue queue;
	protected:
		core::EventMapVoid eventMap;
	};
}
