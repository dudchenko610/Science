#pragma once

#include "../memory-structs/ViewVertex.h"

namespace uifb
{
	namespace interface
	{
		class View 
		{
		public:
			View(unsigned int index, data::ViewVertex* vertex);
		public:
			const glm::f32vec2& GetPos();
			const glm::f32vec2& GetDim();
			const glm::f32vec4& GetColor();
			 
		private:
			data::ViewVertex* vertex;

			unsigned int index;
		};
	}
}



