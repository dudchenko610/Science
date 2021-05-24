#pragma once

#include "glm/glm.hpp"

namespace uifb
{
	namespace data
	{
		struct ViewVertex
		{
			glm::f32vec2 pos;
			glm::f32vec2 dimension;
			glm::f32vec4 color;
			float parentIndex; // maybe union should be used later

			ViewVertex() = default;

		};
	}
}