#include "FunctionalBlock.h"

#include <iostream>

core::FunctionalBlock::FunctionalBlock(core::Window* wnd) : wnd(wnd)
{
	std::cout << "Constructor FunctionalBlock" << std::endl;
}

core::FunctionalBlock::~FunctionalBlock()
{
	std::cout << "Destructor FunctionalBlock" << std::endl;
}

void core::FunctionalBlock::OnStartWindow()
{
	this->OnAssignWindowListeners();
	this->OnAssignSpreaderListeners();
	this->OnInitScene();
}

void core::FunctionalBlock::PrepareEventInWindowThread(core::IEvent* e)
{
	this->windowPrepareEM.ExecuteEvent(e);
}

bool core::FunctionalBlock::CheckEventInSpreaderThread(core::IEvent* e)
{
	return this->eventSprThEM.ExecuteEvent(e);
}


