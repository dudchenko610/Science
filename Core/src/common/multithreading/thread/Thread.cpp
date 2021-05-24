#include <utility>

#include "Thread.h"

#include <iostream>

mthreading::Thread::Thread()
{
	std::cout << "Constructor Thread" << std::endl;
}

mthreading::Thread::~Thread()
{
	std::cout << "Destructor Thread" << std::endl;
}

