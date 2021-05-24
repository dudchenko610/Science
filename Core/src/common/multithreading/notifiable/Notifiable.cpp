#include "Notifiable.h"

#include <iostream>

mthreading::Notifiable::Notifiable()
{
	std::cout << "Constructor Notifiable" << std::endl;
}

mthreading::Notifiable::~Notifiable()
{
	std::cout << "Destructor Notifiable" << std::endl;
}

void mthreading::Notifiable::NotifyOne()
{
	this->condVar.notify_one();
}

void mthreading::Notifiable::NotifyAll()
{
	this->condVar.notify_all();
}

