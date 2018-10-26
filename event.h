#pragma once
#include "delegate.h"
#include <map>
#include <string>
#include <vector>

template<typename...Params>
class BaseEvent 
{
public:
	using Delegate_Type = Delegate<Params...>;

	virtual void addCallback(const std::string, const Delegate_Type&) = 0;
	virtual void removeCallback(const std::string, const Delegate_Type&)=0;
	virtual void removeAllCallbacks() = 0;
	virtual void fire(Params...)=0;

};


template<typename...Params>
class Event:public BaseEvent<Params...>
{

public:
	using Delegate_Type = Delegate<Params...>;
	//! add a unique descriptor to a delegate
	using DelegateMap = std::map<std::string, Delegate_Type>;
private:
	DelegateMap delegateMap;

public:
	Event();
	virtual ~Event();
	virtual void addCallback(const std::string desc, const Delegate_Type&);
	virtual void removeCallback(const std::string desc, const Delegate_Type&);
	virtual void removeAllCallbacks();
	virtual void fire(Params...);
	size_t get_total_registered_callbacks_count() const;
};