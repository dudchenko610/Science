#pragma once

#include <map>
#include <functional>
#include <string>
#include <iostream>


class Factory {
	static std::map< std::string, int > s_creators;
//	static std::map< std::string, std::function< B*() > > s_creators;
	static int s_counter;

public:

	template<class T>
	static void registerClass(const std::string& name) {
		const auto it = s_creators.find(name);
		if (it != s_creators.end()) return; // id was given already

		T::id = s_counter++;

		s_creators[name] = 0;

		/*s_creators[name] = 

			[i]()
			{ 
				
				T* t = new T();
				t->clazzId = i;
				return t;
			};*/
	}

	/*
	template<class T, class ...TParams>
	static T* create(const std::string& name, TParams... params) {
		const auto it = s_creators.find(name);
		
		if (it == s_creators.end()) return nullptr; // not a derived class

		//T* ptr =;
	//	ptr->Init(params...);

		return (T*) (it->second)();
	}
	*/

	static void printRegisteredClasses() {
		for (auto it = s_creators.begin(); it != s_creators.end(); ++it)
			std::cout << it->first << std::endl;
	}
};

std::map< std::string, int > Factory::s_creators;
//template<class B> std::map< std::string, std::function<B*()> > Factory<B>::s_creators;

int Factory::s_counter = 0;

template<class T>
class Creator {
public:
	Creator(const std::string& name) {
		Factory::template registerClass<T>(name);
	}
};

#define REGISTER(derived_class) \
  Creator<derived_class> s_##derived_class##Creator(#derived_class);

