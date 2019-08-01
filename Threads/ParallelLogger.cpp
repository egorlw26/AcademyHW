#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <atomic>
#include <ctime>
#include <thread>
#include <mutex>

class ParallelLogger
{
public:
	ParallelLogger(const std::string& file_name);
	void Log(const std::string& str);
	~ParallelLogger();
private:
	std::string m_file_name;
	std::mutex m_mutex;
};

ParallelLogger::ParallelLogger(const std::string& file_name)
	: m_file_name(file_name)
{};

ParallelLogger::~ParallelLogger()
{};

void ParallelLogger::Log(const std::string& str)
{
	std::ofstream out(m_file_name, std::ios::app);
	if (!out.is_open())
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		if (!out.is_open())
			out.open(m_file_name, std::ios::app);
	}

	std::lock_guard<std::mutex> guard(m_mutex);
	out << str << std::endl;
}

int main()
{
	ParallelLogger pl("1.txt");

	std::thread th([&pl] 
	{
		for (size_t i = 0; i < 100; ++i)
			pl.Log("Write from thread");
	});

	std::thread th2([&pl]
	{
		for (size_t i = 0; i < 100; ++i)
			pl.Log("Write from thread2");
	});

	for (size_t i = 0; i < 100; ++i)
		pl.Log("Write from main");

	th.join();
	th2.join();

	system("pause");
	return 0;
}