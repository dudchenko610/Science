#pragma once

namespace core
{
	struct FreeMemory
	{
		FreeMemory() = default;
		FreeMemory(int index, int size) : index(index), size(size) {}

		int index;
		int size;
	};
}