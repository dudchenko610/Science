#include "state_mutex.h"

mthreading::state_mutex::state_mutex(int defState)
	: a(defState)
{
}

bool mthreading::state_mutex::try_lock(int exS, int nextState)
{
	return a.compare_exchange_strong(exS, nextState, std::memory_order_acquire, std::memory_order_acquire);
}

void mthreading::state_mutex::lock(int expectedState, int nextState)
{
	int _exS = expectedState;

	while (!a.compare_exchange_strong(_exS, nextState, std::memory_order_acquire, std::memory_order_acquire))
	{
		_exS = expectedState; // it should be old value
	}
}

void mthreading::state_mutex::lock(int exS1, int exS2, int nextState)
{
	int _exS1 = exS1;
	int _exS2 = exS2;

	while (!(
		a.compare_exchange_strong(_exS1, nextState, std::memory_order_acquire, std::memory_order_acquire)
			||
		a.compare_exchange_strong(_exS2, nextState, std::memory_order_acquire, std::memory_order_acquire)
		))
	{
		_exS1 = exS1; // it should be old value
		_exS2 = exS2;
	}
}

void mthreading::state_mutex::unlock(int state)
{
	a.store(state, std::memory_order_release);
}
