#pragma once

#include <mutex>

namespace core
{
	template<class D>
	class Identifiable
	{
		static int InstanceCounter;
	public:
		Identifiable()
		{
			std::lock_guard<std::mutex> lg(mtx);
			id = InstanceCounter++; // atomic variable should be here
		}
	public:
		int GetId()
		{
			return id;
		}
	private:
		std::mutex mtx;
		int id;
	};

	template<class D> int Identifiable<D>::InstanceCounter = 0;
}



