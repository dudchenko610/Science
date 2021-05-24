#pragma once

#include <unordered_map>

#include "collections/array-list/ArrayList.h"


class FunctionalBlock;

namespace core
{
	class MemBlock
	{
	protected:
		FunctionalBlock* parentFB;
		std::unordered_map< FunctionalBlock*, collection::ArrayList<MemBlock*>* > listenersMap;
	};
}


