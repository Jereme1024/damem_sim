#ifndef __SCHEDULER_TEST_HPP__
#define __SCHEDULER_TEST_HPP__

#include "../include/damemory.hpp"
#include <cassert>

template <template <class> class Scheduler_type, class Struct_type>
class Scheduler_test
{
private:
	static const int max_size = 4;
	static const int total_size = 6;
	Scheduler<Struct_type> *scheduler;

public:
	void LRU_test()
	{
		Scheduler_LRU<Struct_type> lru(max_size);
		Page *page[total_size];

		for (int i = 0; i < total_size; i++)
		{
			std::string name = "tmp." + std::to_string(i);
			page[i] = new Page(name);

			lru.on_schedule(page[i]);
			// sched: 5, 4, 3, 2
		}
		
		std::cerr << "LRU size test\n";
		assert (lru.get_size() == max_size);
		assert (!lru.is_hit(page[0]));

		std::cerr << "evict_one() test\n";
		lru.evict_one();
		assert (lru.get_size() == (max_size - 1));
		assert (!lru.is_hit(page[2]));
		// sched: 5 4 3
		
		std::cerr << "off_schedule(...) test\n";
		lru.off_schedule(page[5]);
		assert (!lru.is_hit(page[5]));
		// sched: 4 3
		
		std::cerr << "is_hit(...) test\n";
		lru.is_hit(page[3]);
		// sched: 3 4
		lru.evict_one();
		// sched: 3
		assert (lru.is_hit(page[3]) && !lru.is_hit(page[4]));
	}

	void main()
	{
		scheduler = new Scheduler_type<Struct_type>(max_size); 
		LRU_test();
	}
};

#endif
