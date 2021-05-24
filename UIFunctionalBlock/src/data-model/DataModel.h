#pragma once

#include "view/View.h"
#include "glm/glm.hpp"

#include "collections/avl-tree/AVLTree.h"

#include "view/events/ViewEvents.h"
#include "memory-structs/ViewVertex.h"
#include "common/heap/Heap.h"

namespace uifb 
{
	namespace data
	{
		class DataModel
		{
		public:
			DataModel(int viewCount);
			~DataModel();
		public:
			void CreateView(uifb::interface::CreateViewEvent* e);
			void RemoveView(uifb::interface::RemoveViewEvent* e);
			const int GetViewNumber();
			void* GetVertexData();
			void* GetIndexData();

		private:
			int viewCount;

			core::Heap verticesHeap;

			unsigned int* indices;
			interface::View** views;
			
			int index;
		};
	}

}

