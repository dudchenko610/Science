#include "DataModel.h"

#define GROUND_INDEX 0xFFFFFFFF

uifb::data::DataModel::DataModel(int viewCount) :
	viewCount(viewCount),
	index(0),

	indices(new unsigned int[viewCount]),
	views(new interface::View*[viewCount]),
	verticesHeap(sizeof(ViewVertex) * viewCount)
{
}

uifb::data::DataModel::~DataModel()
{
	delete[] indices;
	delete[] views; // iterate through and delete View's
}

void uifb::data::DataModel::CreateView(uifb::interface::CreateViewEvent* e)
{
	std::cout << "void uifb::data::DataModel::CreateView(uifb::interface::CreateViewEvent* e)" << std::endl;

	ViewVertex* vV = verticesHeap.Allocate<ViewVertex>();

	std::cout << "int index = verticesHeap.IndexOf<ViewVertex>(vV);" << std::endl;

	int index = verticesHeap.IndexOf<ViewVertex>(vV);

	vV->color = e->color;
	vV->pos = e->pos;
	vV->dimension = e->dim;
	vV->parentIndex = GROUND_INDEX;

	this->indices[this->index++] = index;
	this->views[index] = new interface::View(index, vV);
}

void uifb::data::DataModel::RemoveView(uifb::interface::RemoveViewEvent* e)
{

}

const int uifb::data::DataModel::GetViewNumber()
{
	return this->index;
}

void* uifb::data::DataModel::GetVertexData()
{
	return this->verticesHeap.GetData();
}

void* uifb::data::DataModel::GetIndexData()
{
	return this->indices;
}
