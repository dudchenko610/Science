#pragma once

#include "../../common/multithreading/synchronizers/resolver-thread/resolver-blocking-thread/ResolverBlockingThread.h"
#include "../../events/IEvent.h"
#include "collections/array-list/ArrayList.h"

namespace core
{

	class Window;
	class FunctionalBlock;

	class EventSpreaderThread : public mthreading::ResolverBlockingThread
	{
	public:
		EventSpreaderThread(core::Window* wnd);
		virtual ~EventSpreaderThread();
	public:
		void PushEvent(core::IEvent* e) override;
	protected:
		void OnHandleEvent(core::IEvent* e) override;
	protected:
		void OnStarted() override;
		void OnStoped() override;
	private:
		core::Window* wnd;
		collection::ArrayList<FunctionalBlock*>* functionalBlocks;
	};
}



