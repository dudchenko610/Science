#pragma once
#include <thread>

namespace mthreading 
{
	class Thread
	{
	protected:
		Thread();
		virtual ~Thread();
	public:
		template<class T, class ...TParams>
		static T* StartThread(TParams... params)
		{
			Thread* th = new T(params...);
			th->thread = std::move(std::thread(&Thread::Run, th));
			th->thread.detach();

			return (T*) th;
		}

	protected:
		virtual void Run() = 0;

	private:
		std::thread thread;
	};
}



