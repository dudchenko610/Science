#pragma once

#include <map>
#include <functional>
#include <string>
#include <iostream>



namespace core
{
	class EventFactory {
		static std::map< std::string, int > s_creators;
		static int s_counter;
		static int s_max;

	public:

		template<class T>
		static void RegisterClass(const std::string& name) 
		{
			const auto it = s_creators.find(name);
			if (it != s_creators.end()) return;

			T::id = s_counter++;

			int sizeOfT = sizeof(T);
			if (sizeOfT > s_max)
			{
				s_max = sizeOfT;
			}

			s_creators[name] = 0;
		}

		static void PrintRegisteredClasses() 
		{
			for (auto it = s_creators.begin(); it != s_creators.end(); ++it)
				std::cout << it->first << std::endl;
		}

		static const int GetEventTypeCount() 
		{
			return s_counter;
		}

		static const int GetMaxEventSize()
		{
			return s_max;
		}
	};

	

	template<class T>
	class EventCreator {
	public:
		EventCreator(const std::string& name) {
			EventFactory::template RegisterClass<T>(name);
		}
	};

}



#define REGISTER_EVENT(derived_class) \
  core::EventCreator<derived_class> s_##derived_class##Creator(#derived_class);
