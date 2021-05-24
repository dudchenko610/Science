#include "spinlock_mutex.h"



void mthreading::spinlock_mutex::lock()
{
	while (flag.test_and_set(std::memory_order_acquire));
}

void mthreading::spinlock_mutex::unlock()
{
	flag.clear(std::memory_order_release);
}
