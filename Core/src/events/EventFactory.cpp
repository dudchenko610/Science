#include "EventFactory.h"

std::map< std::string, int > core::EventFactory::s_creators;
int core::EventFactory::s_counter = 0;
int core::EventFactory::s_max = 0;