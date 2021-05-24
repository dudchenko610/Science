#pragma once

#include <functional>

#include "IEvent.h"

#include <iostream>

namespace core
{
	class EventMapVoid
	{
	public:
		EventMapVoid();
		~EventMapVoid();
	public:
		template<class T>
		void SetEventLogic(std::function< void(T*) > func)
		{
			map[T::GetEventType()] =
				[=](core::IEvent* e)
			{
				T* t = (T*)e;
				func(t);
			};
		}

		void ExecuteEvent(core::IEvent* e);
	private:
		std::function<void(core::IEvent*)>* map;
	};

}