#pragma once

#include "../Queue.h"
#include <mutex>

namespace collection 
{
	template<typename T>
	class QueueSafe : Queue<T>
	{
	public:
		void Push(T data)
		{
			std::lock_guard<std::mutex> lg(mtx);
			Queue<T>::Push(data);
		}

		T Pop()
		{
			std::lock_guard<std::mutex> lg(mtx);
			T data = Queue<T>::Pop();

			return data;
		}

		int GetSize() const
		{
			std::lock_guard<std::mutex> lg(mtx);
			int size = Queue<T>::GetSize();

			return size;
		}

		template<typename Functor>
		void ForEach(Functor functor)
		{
			std::lock_guard<std::mutex> lg(mtx);
			Queue<T>::ForEach(functor);
		}

		template<typename Functor>
		void ForEachRemoving(Functor functor)
		{
			std::lock_guard<std::mutex> lg(mtx);
			Queue<T>::ForEachRemoving(functor);
		}

		void Clean()
		{
			std::lock_guard<std::mutex> lg(mtx);
			Queue<T>::Clean();
		}

		bool IsEmpty() const
		{
			return Queue<T>::IsEmpty();
		}


	private:
		std::mutex mtx;
	};
}



