#pragma once

#include <atomic>

namespace mthreading
{
	class spinlock_mutex
	{
	public:
		spinlock_mutex() = default;
		void lock();
		void unlock();
	private:
		std::atomic_flag flag = ATOMIC_FLAG_INIT;
	};
}



