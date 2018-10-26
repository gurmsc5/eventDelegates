#ifndef CALLBACK_H
#define CALLBACK_H
#include <functional>



//! \author: GSC
//! \brief: Delegate function wrapper around non-class functions
//! Example usage:
//! Delegate<> my_del; void myfunc(void);
//! my_del(Bind_Func(myfunc);				   --> rvalue
//! auto res = Bind_Func(myfunc); my_del(res); --> lvalue
	
template<typename... Params>
std::function<void(Params...)> Bind_Func(void(*func)(Params...))
{
	return func;
}

template<typename... Params>
class Delegate:public std::function<void(Params...)>
{
public:
	using callback_func = std::function<void(Params...)>;
	Delegate() :callback_func(placeholder_func) {};

	template<typename Func>
	Delegate(const Func &cb_func) :callback_func(cb_func) {};

	template<typename Func>
	Delegate( Func &&cb_func) :callback_func(std::move(cb_func)) {};

private:
	static void placeholder_func(Params...) {};

};


#endif