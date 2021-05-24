#pragma once

#include "../FunctionalBlock.h"
#include "../../common/multithreading/synchronizers/resolver-thread/resolver-blocking-thread/ResolverBlockingThread.h"

namespace core
{
	class BlockingFunctionalBlock : public mthreading::ResolverBlockingThread, public FunctionalBlock
	{
	protected:
		BlockingFunctionalBlock(core::Window* wnd);
		virtual ~BlockingFunctionalBlock();
	public:
		void PushEvent(core::IEvent* e) override;
		void OnStoped() override;

		// handle event override, and call it in child class
	};
}



