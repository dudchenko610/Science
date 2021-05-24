#pragma once

#include "../../window/Window.h"
#include "../../events/IEvent.h"

namespace app
{

	class OpenWindowEvent : public core::IEvent, public core::Base<OpenWindowEvent>
	{
	public:
		OpenWindowEvent(core::Window* wnd) : core::IEvent(id, byteSize), wnd(wnd) {}
	public:
		core::Window* wnd;
	};


	class TerminateProgramEvent : public core::IEvent, public core::Base<TerminateProgramEvent>
	{
	public:
		TerminateProgramEvent() : core::IEvent(id, byteSize) {}
	};


	class WindowCrushedEvent : public core::IEvent, public core::Base<WindowCrushedEvent>
	{
	public:
		WindowCrushedEvent(core::Window* wnd) : core::IEvent(id, byteSize), wnd(wnd) {}
	public:
		core::Window* wnd;
	};

}