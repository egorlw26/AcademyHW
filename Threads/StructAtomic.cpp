#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>

struct SimpleStruct
{
	SimpleStruct() = default;
	SimpleStruct operator+(float val);
	float get() const;
	float m_value = 0;
};


SimpleStruct SimpleStruct::operator+(float arg)
{
	SimpleStruct r;
	r.m_value = m_value + arg;
	return r;
}

float SimpleStruct::get() const 
{
	return m_value;
}

int main()
{
	std::atomic<SimpleStruct> ss;
	

	std::thread th([&ss]
	{
		for (size_t i = 0; i < 10000; ++i)
		{
			SimpleStruct tss = ss;
			while (!ss.compare_exchange_weak(tss, tss + 1));
		}
	});

	for (size_t i = 0; i < 10000; ++i)
	{
		SimpleStruct tss = ss;
		while (!ss.compare_exchange_weak(tss, tss + 1));
	}

	th.join();

	std::cout << ss.load().get() << std::endl;

	system("pause");
	return 0;
}