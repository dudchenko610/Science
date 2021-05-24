#pragma once

#include <functional>
#include "IEvent.h"
#include <iostream>
#include "EventFactory.h"

namespace core
{

	template<class B>
	class EventMap
	{
	public:
		EventMap() 
		{
			map = new std::function<B(core::IEvent*)>[core::EventFactory::GetEventTypeCount()];

			for (int i = 0; i < core::EventFactory::GetEventTypeCount(); i ++)
			{
				map[i] = [](core::IEvent* e)
				{
					return 0;
				};
			}
		}
		~EventMap()
		{
			delete[] map;
		}
	public:
		template<class T>
		void SetEventLogic(std::function< B(T*) > func)
		{
			map[T::GetEventType()] =
				[=](core::IEvent* e)
			{
				T* t = (T*)e;
				return func(t);
			};
		}

		B ExecuteEvent(core::IEvent* e)
		{
			std::function<B(core::IEvent*)> func = map[e->GetType()];
			return func(e);
		}
	private:
		std::function<B(core::IEvent*)>* map;
	};
}