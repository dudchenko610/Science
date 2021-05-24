#pragma once

#include "../FunctionalBlock.h"
#include "../../common/multithreading/synchronizers/resolver-thread/resolver-worker-thread/ResolverWorkerThread.h"

namespace core
{
	class WorkerFunctionalBlock : public FunctionalBlock, public mthreading::ResolverWorkerThread
	{
	protected:
		WorkerFunctionalBlock(core::Window* wnd);
		virtual ~WorkerFunctionalBlock();
	protected:
		void Run() override;
		void OnStoped() override;
	protected:
		virtual void OnUpdate() = 0;
	};
}



