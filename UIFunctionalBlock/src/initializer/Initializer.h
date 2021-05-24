#pragma once

#include <functional>
#include "../data-model/view/events/ViewEvents.h"

#include "events/EventFactory.h"

namespace uifb
{
	void InitCore(std::function< void() > func)
	{
		using namespace interface;

		REGISTER_EVENT(CreateViewEvent);
		REGISTER_EVENT(UpdateViewEvent);
		REGISTER_EVENT(RemoveViewEvent);

		func();
	}
}