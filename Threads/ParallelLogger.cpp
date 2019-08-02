#include <iostream>
#include <fstream>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>

class ParallelLogger
{
public:
	ParallelLogger(const std::string& file_name);
	void LogMutex(const std::string& str);
	void LogCallOnce(const std::string& str);
	~ParallelLogger();
private:
	std::string m_file_name;
	std::ofstream m_ofs;
	std::mutex m_mutex;
	std::once_flag m_flag;
};

ParallelLogger::ParallelLogger(const std::string& file_name)
	: m_file_name(file_name)
{};

ParallelLogger::~ParallelLogger()
{
	if (m_ofs.is_open())
		m_ofs.close();
};

void ParallelLogger::LogMutex(const std::string& str)
{
	if (!m_ofs.is_open())
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		if (!m_ofs.is_open())
		{
			m_ofs.open(m_file_name, std::ios::app);
			m_ofs << "Mutex\n";
		}
	}
	std::lock_guard<std::mutex> guard(m_mutex);
	m_ofs << str << std::endl;
}

void ParallelLogger::LogCallOnce(const std::string& str)
{
	std::call_once(m_flag, [this]
	{
		this->m_ofs.open(this->m_file_name);
		std::lock_guard<std::mutex> guard(this->m_mutex);
		this->m_ofs << "CallOnce\n";
	});

	std::lock_guard<std::mutex> guard(m_mutex);
	m_ofs << str << std::endl;
}

int main()
{
	ParallelLogger pl("test.txt");

	std::thread th([&pl]
	{
		for (size_t i = 0; i < 100; ++i)
			pl.LogMutex("Write from thread");
	});

	for (size_t i = 0; i < 100; ++i)
		pl.LogMutex("Write from main");

	th.join();

	system("pause");
	return 0;
}