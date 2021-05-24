#pragma once

#include "events/IEvent.h"
#include "glm/glm.hpp"
//#include "common/variadic-struct/Tuple.h"

namespace uifb
{
	namespace interface
	{
		class CreateViewEvent : public core::IEvent, public core::Base<CreateViewEvent>
		{
		public:
			CreateViewEvent(glm::f32vec2& pos, glm::f32vec2& dim, glm::f32vec4& color) :
				IEvent(id, byteSize),
				pos(pos), dim(dim), color(color)
			{}

			CreateViewEvent(glm::f32vec2&& pos, glm::f32vec2&& dim, glm::f32vec4&& color) :
				IEvent(id, byteSize),
				pos(pos), dim(dim), color(color)
			{}
			
			glm::f32vec2 pos;
			glm::f32vec2 dim;
			glm::f32vec4 color;

		};

		class UpdateViewEvent : public core::IEvent, public core::Base<UpdateViewEvent>
		{
		public:
			UpdateViewEvent() : IEvent(id, byteSize) {}
		};

		class RemoveViewEvent : public core::IEvent, public core::Base<RemoveViewEvent>
		{
		public:
			RemoveViewEvent() : IEvent(id, byteSize) {}
		};
	};
}



