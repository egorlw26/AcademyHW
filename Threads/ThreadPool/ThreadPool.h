#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <atomic>
#include <future>
#include <functional>
#include <memory>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <string>


class ThreadPool
{
public:
	ThreadPool(const size_t size = 0);

	std::future<void> ToDo(const std::function<void()>& i_func);

	template<typename Func, typename... Args, typename = std::enable_if_t<!std::is_void<std::result_of_t<Func(Args...)>>::value>>
	std::future<typename std::result_of<Func(Args...)>::type> ToDo(Func&& i_func, Args&&... i_args);

	~ThreadPool();

private:
	void Log(const std::string& i_message);
	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
	std::mutex m_tasks_mutex;
	std::mutex m_log_mutex;
	std::atomic<size_t> num_of_active_threads;
	std::condition_variable m_cond_var;
	bool finish;

};

template<typename Func, typename... Args, typename = std::enable_if_t<!std::is_void<std::result_of_t<Func(Args...)>>::value>>
std::future<typename std::result_of<Func(Args...)>::type> ThreadPool::ToDo(Func&& i_func, Args&&... i_args)
{

	using r_type = typename std::result_of<Func(Args...)>::type;

	auto task = std::make_shared<std::promise<r_type>>();

	std::future<r_type> res_f = task->get_future();

	{
		std::unique_lock<std::mutex> u_lock(m_tasks_mutex);
		m_tasks.push([task, i_func, i_args...]{ task->set_value(i_func(std::forward<Args...>(i_args)...)); });
	}

	m_cond_var.notify_one();
	return res_f;
}
