#pragma once

#include "../HoldingQueue.h"
#include <mutex>

namespace collection
{
	class HoldingQueueSafe : HoldingQueue
	{
	public:


		void Push(int typeSize, void* data)
		{
			std::lock_guard<std::mutex> lg(mtx);
			HoldingQueue::Push(typeSize, data);
		}

		void Pop(void* data)
		{
			std::lock_guard<std::mutex> lg(mtx);
			HoldingQueue::Pop(data);
		}

		int GetSize()
		{
			std::lock_guard<std::mutex> lg(mtx);
			int size = HoldingQueue::GetSize();

			return size;
		}


		void Clean()
		{
			std::lock_guard<std::mutex> lg(mtx);
			HoldingQueue::Clean();
		}

		bool IsEmpty() const
		{
			return HoldingQueue::IsEmpty();
		}


	private:
		std::mutex mtx;
	};
}



