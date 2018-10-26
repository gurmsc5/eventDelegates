#include "event.h"
#include <iostream>
#define DEBUG_MODE

template <typename...Params>
Event<Params...>::Event():delegateMap()
{}

template<typename ...Params>
Event<Params...>::~Event()
{
	removeAllCallbacks();
}

template<typename ...Params>
void Event<Params...>::addCallback(const std::string desc, const Delegate_Type &del)
{
	delegateMap.insert(std::make_pair(desc, del));
#ifdef DEBUG_MODE
	std::cout << "-----Callback event with name: " << desc << " added-----" << std::endl;
#endif
}

template<typename ...Params>
void Event<Params...>::removeCallback(const std::string desc, const Delegate_Type &del)
{
	auto it = delegateMap.find(desc);
	if (it != delegateMap.end()) {
		delegateMap.erase(it);
#ifdef DEBUG_MODE
		std::cout << "-----Callback event with name: " << desc << " removed------" << std::endl;
#endif
	}
}

template<typename ...Params>
void Event<Params...>::removeAllCallbacks()
{
	delegateMap.clear();
#ifdef DEBUG_MODE
	std::cout << "-----All events removed-----" << std::endl;
#endif
}

template<typename ...Params>
void Event<Params...>::fire(Params ...params)
{
	for (auto &it:delegateMap)
	{
#ifdef DEBUG_MODE
		std::cout << "-----Callback event with name: " << it.first << " to be fired-----" << std::endl;
#endif
		(it.second)(std::forward<Params>(params)...);
	}
}

template<typename ...Params>
size_t Event<Params...>::get_total_registered_callbacks_count() const
{
	return delegateMap.size();
}
