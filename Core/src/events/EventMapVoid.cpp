#include "EventMapVoid.h"

#include "EventFactory.h"

core::EventMapVoid::EventMapVoid() : map(nullptr)
{
	std::cout << "!!!!!!!! core::EventFactory::GetEventTypeCount() = " << core::EventFactory::GetEventTypeCount() << std::endl;
	map = new std::function<void( core::IEvent* )>[ core::EventFactory::GetEventTypeCount() ];

	for (int i = 0; i < core::EventFactory::GetEventTypeCount(); i++)
	{
		map[i] = [](core::IEvent* e)
		{
		};
	}
}

core::EventMapVoid::~EventMapVoid()
{
	delete[] map;
}

void core::EventMapVoid::ExecuteEvent(core::IEvent* e)
{
	// checking for nullptr required
	std::function<void(core::IEvent*)> func = map[e->GetType()];
	func(e);
}


