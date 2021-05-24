#pragma once

#include <atomic>

namespace mthreading
{
	class state_mutex
	{
	public:
		state_mutex(int defState);
	public:
		bool try_lock(int exS, int nextState);
		void lock(int exS, int nextState);
		void lock(int exS1, int exS2, int nextState);
		void unlock(int state);
	private:
		std::atomic<int> a;
	};
}



