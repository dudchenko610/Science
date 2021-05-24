#pragma once

#include <functional>

#include "../events/EventFactory.h"

#include "events/AppEvents.h"
#include "../common/multithreading/events/thread-events/ThreadEvents.h"
#include "../window/events/MouseEvents.h"
#include "../window/events/KeyboardEvents.h"




namespace core
{
	void InitCore(std::function< void() > func)
	{
		using namespace app;

		REGISTER_EVENT(OpenWindowEvent);        // 0
		REGISTER_EVENT(TerminateProgramEvent);  // 1
		REGISTER_EVENT(WindowCrushedEvent);     // 2

		using namespace mthreading;

		REGISTER_EVENT(StopThreadEvent);        // 3
		REGISTER_EVENT(ThreadStopedEvent);      // 4

		using namespace core::mouse;

		REGISTER_EVENT(ClickEvent);
		REGISTER_EVENT(MoveEvent);
		REGISTER_EVENT(ScrollEvent);



	//	using namespace core::keyboard;

	//	REGISTER_EVENT();


		func();

		std::cout << "Size in bytes: " << OpenWindowEvent::GetSizeInBytes() << " " << sizeof(OpenWindowEvent) << " " << OpenWindowEvent::GetEventType() <<  std::endl;
		std::cout << "Size in bytes: " << TerminateProgramEvent::GetSizeInBytes() << " " << sizeof(TerminateProgramEvent) << " " << TerminateProgramEvent::GetEventType() << std::endl;
		std::cout << "Size in bytes: " << StopThreadEvent::GetSizeInBytes() << " " << sizeof(StopThreadEvent) << " " << StopThreadEvent::GetEventType() << std::endl;
		std::cout << "Size in bytes: " << ThreadStopedEvent::GetSizeInBytes() << " " << sizeof(ThreadStopedEvent) << " " << ThreadStopedEvent::GetEventType() << std::endl;


		std::cout << "Size in bytes: " << ClickEvent::GetSizeInBytes() << " " << sizeof(ClickEvent) << " " << ClickEvent::GetEventType() << std::endl;

		StopThreadEvent ste;

		std::cout << "StopThreadEvent type: " << ste.GetType() << std::endl;
	}
}