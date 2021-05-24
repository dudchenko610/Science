#include "View.h"

uifb::interface::View::View(unsigned int index, data::ViewVertex* vertex) :
	index(index), vertex(vertex)
{
}

const glm::f32vec2& uifb::interface::View::GetPos()
{
	return this->vertex->pos;
}

const glm::f32vec2& uifb::interface::View::GetDim()
{
	return this->vertex->dimension;
}

const glm::f32vec4& uifb::interface::View::GetColor()
{
	return this->vertex->color;
}
