#include "gtest/gtest.h"
#include "event.h"
#include "event.cpp"
#include <iostream>

void test1()
{
	std::cout << "test1" << std::endl;
}
void test2()
{
	std::cout << "test2" << std::endl;

}

void test3(int val)
{

	std::cout << "test3: " << val << std::endl;
}

TEST(EventAddTest, EventDelegate)
{
	Event<> my_event;
	Delegate<> my_del1(Bind_Func(test1));
	Delegate<> my_del2(Bind_Func(test2));


	my_event.addCallback("my_del1",my_del1);
	my_event.addCallback("my_del2", my_del2);

	ASSERT_EQ(my_event.get_total_registered_callbacks_count(),2);
	
}

TEST(EventFireTest, EventDelegate)
{
	Event<int> my_event;
	Delegate<int> my_del1(Bind_Func(test3));
	Delegate<int> my_del2(Bind_Func(test3));
	Delegate<int> my_del3(Bind_Func(test3));

	my_event.addCallback("my_del1", my_del1);
	my_event.addCallback("my_del2", my_del2);

	ASSERT_EQ(my_event.get_total_registered_callbacks_count(), 2);

	my_event.fire(5);
	
	my_event.addCallback("my_del3",my_del3);

	my_event.fire_unique_callback("my_del3", 30);
}
