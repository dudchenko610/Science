#pragma once

#include <GL/glew.h>

#include "../common/multithreading/synchronizers/resolver-thread/ResolverThread.h"
#include "../common/multithreading/thread/Thread.h"
#include "../events/IEvent.h"

#include "collections/array-list/ArrayList.h"

#include "../store/mem-block/MemBlock.h"

#include "glm/glm.hpp"

#include "../common/identifiable/Identifiable.h"

#include "../events/EventMapVoid.h"
#include "../events/EventMap.h"

namespace core
{
	class Window;
//	class EventSpreaderThread;

	class FunctionalBlock
	{
	friend class EventSpreaderThread;

	protected:
		FunctionalBlock(Window* wnd);
	public:
		virtual ~FunctionalBlock();
	public:
		virtual void PushEvent(core::IEvent* e) = 0;
	public:
		virtual void OnStartWindow();
		virtual void OnInitScene() = 0;
		virtual void OnAssignWindowListeners() = 0;
		virtual void OnAssignSpreaderListeners() = 0;


		virtual void OnUpdateWindow(float dt, float time) = 0;

	public:
		virtual void PrepareEventInWindowThread(core::IEvent* e);
		virtual bool CheckEventInSpreaderThread(core::IEvent* e);
	protected:
		collection::ArrayList<MemBlock*> memBlocks;
		Window* wnd;

		core::EventMapVoid windowPrepareEM;
		core::EventMap<bool> eventSprThEM;
	};
}

