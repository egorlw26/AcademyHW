#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <ctime>
#include <thread>


template<typename T>
T straight_func_sum(T val, const std::vector<T>& vec, const std::function<T(T)>& i_func)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		val += i_func(vec[i]);
	}
	return val;
}

template<typename T, typename it>
T parallel_func_sum(T val, it i_begin, it i_end, size_t threads_num, const std::function<T(T)>& i_func)
{
	const size_t num_of_el = std::distance<it>(i_begin, i_end);
	const size_t portion = ceil((double)num_of_el / threads_num);
	std::vector<T> thread_sum(threads_num, 0);
	std::vector<std::thread> thread_vec(threads_num);
	for (size_t i = 0; i < threads_num; ++i)
	{
		thread_vec[i] = std::thread([&portion, i, &num_of_el, &thread_sum, &i_begin, &i_end, &i_func]
		{
			T sum = 0;
			for (size_t j = 0; j < portion; ++j)
				if (i * portion + j < num_of_el)
					sum += i_func(*(i_begin + i * portion + j));
				else
					break;
			thread_sum[i] = sum;
		}
		);
	}

	for (size_t i = 0; i < threads_num; ++i)
		thread_vec[i].join();

	for (T v : thread_sum)
		val += v;

	return val;
}


int main()
{
	std::vector<double> test_vec;
	srand(time(NULL));
	for (size_t i = 0; i < 10000; ++i)
		test_vec.push_back(rand() % 100);
	std::cout << "Generated vector\n";

	auto s_start = std::clock();

	double straight_val = 0;
	straight_val = straight_func_sum<double>(straight_val, test_vec, [](double i) {return i; });
	std::cout << "Straight solution returned: " << straight_val << std::endl;

	auto s_end = std::clock();

	std::cout << "Straight : " << (s_end - s_start) / (double)CLOCKS_PER_SEC << std::endl;

	auto p_start = std::clock();

	double parallel_val = 0;
	parallel_val = parallel_func_sum<double>(parallel_val, test_vec.begin(), test_vec.end(), std::thread::hardware_concurrency(), [](double i) {return i; });
	std::cout << "Parallel solution returned: " << parallel_val << std::endl;

	auto p_end = std::clock();

	std::cout << "Parallel : " << (p_end - p_start) / (double)CLOCKS_PER_SEC << std::endl;

	std::cout << "SpeedUp : " << ((s_end - s_start)/ (double)CLOCKS_PER_SEC) / ((p_end - p_start) / (double)CLOCKS_PER_SEC) << std::endl;


	system("pause");
	return 0;
}