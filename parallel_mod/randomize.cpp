#include "randomize.h"
#include <random>
#include <chrono>
#include <vector>
#include <chrono>
#include <thread>
#include <climits>

#ifdef _MSC_VER
#pragma warning (disable: 4146)
#endif //_MSC_VER

void randomize(void* pData, std::size_t cbData)
{
	std::size_t T = std::thread::hardware_concurrency();
	std::uintptr_t seed = std::chrono::system_clock::now().time_since_epoch().count() % std::minstd_rand::modulus;
	std::vector<long long> thread_seed_multipliers;
	thread_seed_multipliers.reserve(T);
	thread_seed_multipliers.emplace_back(1u);
	for (std::size_t i = 1; i < T; ++i)
		thread_seed_multipliers.emplace_back((thread_seed_multipliers.back() * std::minstd_rand::multiplier) % std::minstd_rand::modulus);
	auto thread_fn = [T, seed, pData, cbData, &thread_seed_multipliers](std::size_t t)
	{
		std::uintptr_t* words = (std::uintptr_t*) pData;
		std::size_t element_count = cbData / sizeof(std::uintptr_t);
		std::size_t bytes_rest = cbData % sizeof(std::uintptr_t);
		std::size_t block_size = element_count / T;
		std::size_t block_extra = element_count % T;
		std::size_t begin = t < block_extra?++block_size * t:block_extra + t * block_size, end = begin + block_size;
		std::uniform_int_distribution<std::uintptr_t> dis;
		std::minstd_rand gen{static_cast<unsigned>(seed * thread_seed_multipliers[t] % std::minstd_rand::modulus + 
			std::minstd_rand::increment * (thread_seed_multipliers[t] - 1) / (std::minstd_rand::multiplier - 1))};
		for (auto i = begin; i < end; ++i)
			words[i] = dis(gen);
		if (bytes_rest && t == T - 1)
		{
			auto last_word = dis(gen);
			unsigned char* last_data = (unsigned char*) (words + element_count);
			do
			{
				*last_data++ = static_cast<unsigned char>(last_word & ~(-static_cast<std::uintptr_t>(-1) << CHAR_BIT));
				last_word >>= CHAR_BIT;
			}while(--bytes_rest);
		}
	};
	std::vector<std::thread> workers;
	workers.reserve(T);
	for (std::size_t t = 1; t < T; ++t)
		workers.emplace_back(thread_fn, t);
	thread_fn(0);
	for (auto& thr:workers)
		thr.join();
}
