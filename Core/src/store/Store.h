#pragma once

namespace core
{
	class Store
	{
	public:
		Store(const Store&) = delete;

		static Store& Get();
	private:
		Store();
		~Store();
	};
}



