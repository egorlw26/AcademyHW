#include "ThreadPool.h"
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


int main()
{
	{
		ThreadPool pool(4);
		std::vector< std::future<int> > results;

		for (int i = 0; i < 4; ++i) {
			results.emplace_back(pool.ToDo([i] {
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return i * i;
			})
			);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		for (int i = 0; i < 4; ++i) {
			results.emplace_back(
				pool.ToDo([i] {
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return i * i;
			})
			);
		}

		for (auto && result : results)
			result.get();
	}


	
	system("pause");
	return 0;
}