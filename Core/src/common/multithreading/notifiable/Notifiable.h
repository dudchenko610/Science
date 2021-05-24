#pragma once

#include <mutex>
#include <condition_variable>

namespace mthreading
{
	class Notifiable
	{
	public:
		Notifiable();
		~Notifiable();
	public:
		template <class _ConditionalPredicate, class _SharedPrediate>
		void Wait(_ConditionalPredicate condPred, _SharedPrediate shdPred)
		{
			std::unique_lock<std::mutex> ul(mtx);
			condVar.wait(ul, condPred);
			
			shdPred();
			// unlocking after stack pops up
		}

		template <class _ConditionalPredicate>
		void Wait(_ConditionalPredicate condPred)
		{
			std::unique_lock<std::mutex> ul(mtx);
			condVar.wait(ul, condPred);
		}

		void NotifyOne();
		void NotifyAll();

		template <class _Predicate>
		void DoSync(_Predicate predicate)
		{
			std::lock_guard<std::mutex> lg(mtx);
			predicate();
		}

	private:
		std::mutex mtx;
		std::condition_variable condVar;
	};

}


