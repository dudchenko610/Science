#pragma once

#include "../../events/IEvent.h"

namespace core 
{
	namespace mouse
	{
		class ClickEvent : public core::IEvent, public core::Base<ClickEvent>
		{
		public:
			ClickEvent(int button, int action, int mods) :
				IEvent(id, byteSize),
				button(button),
				action(action),
				mods(mods),
				out_data{ 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF }
			{}

			int button;
			int action;
			int mods;

			unsigned int out_data[4];
		};

		class MoveEvent : public core::IEvent, public core::Base<ClickEvent>
		{
		public:
			MoveEvent(double xpos, double ypos) : IEvent(id, byteSize), xpos(xpos), ypos(ypos) {}

			double xpos;
			double ypos;
		};

		class ScrollEvent : public core::IEvent, public core::Base<ClickEvent>
		{
		public:
			ScrollEvent(double xoffset, double yoffset) : IEvent(id, byteSize), xoffset(xoffset), yoffset(yoffset) {}

			double xoffset;
			double yoffset;
		};



	}
}