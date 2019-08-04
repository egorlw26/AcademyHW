#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t size)
	: finish(false)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_threads.push_back(std::thread([this, i]
		{
			bool initialized = false;
			while (true)
			{
				std::function<void()> task;

				if (!initialized)
				{
					Log("Thread" + std::to_string(i) + " initialized");
					initialized = true;
				}

				std::unique_lock<std::mutex> u_lock(m_tasks_mutex);
				m_cond_var.wait(u_lock, [this] {return finish || !m_tasks.empty(); });
				if (finish)
					break;
				Log("Thread " + std::to_string(i) + " started work...");
				++num_of_active_threads;
				task = m_tasks.front();
				m_tasks.pop();

				u_lock.unlock();

				task();

				Log("Thread" + std::to_string(i) + " finished work...");

				u_lock.lock();
				--num_of_active_threads;
				if (!num_of_active_threads && !finish && m_tasks.empty())
					Log("\nAll work is done, waiting for another task...\n");
				u_lock.unlock();

			}
		}));
	}
}

void ThreadPool::Log(const std::string& i_message)
{
	m_log_mutex.lock();
	std::cout << i_message << std::endl;
	m_log_mutex.unlock();
}

ThreadPool::~ThreadPool()
{
	std::unique_lock<std::mutex> u_lock(m_tasks_mutex);
	finish = true;
	u_lock.unlock();

	m_cond_var.notify_all();

	for (std::thread& th : m_threads)
		th.join();
	
	Log("Starting destroying...");

	Log("Thread Pool finished it's job.\n");
}