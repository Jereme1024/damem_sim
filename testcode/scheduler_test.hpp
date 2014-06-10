#ifndef __SCHEDULER_TEST_HPP__
#define __SCHEDULER_TEST_HPP__

#include "../include/damemory.hpp"

template <template <class> class Scheduler_type, class Struct_type>
class Scheduler_test
{
private:
	static const int max_size = 4;
	static const int total_size = 6;
	Scheduler<Struct_type> *scheduler;
	Page *page[total_size];

public:
	void main()
	{
		scheduler = new Scheduler_type<Struct_type>(max_size);

		for (int i = 0; i < total_size; i++)
		{
			std::string name = "tmp." + std::to_string(i);
			page[i] = new Page(name);

			if (!scheduler->is_full())
			{
				scheduler->on_schedule(page[i]);
			}
		}

		std::cout << "** first max_size is hit\n";
		check_hits(); // 3, 2, 1, 0

		std::cout << "** page 3~1 is hit\n";
		scheduler->evict_one(); // 3, 2, 1
		check_hits();
		std::cout << "** is_full " << scheduler->is_full() << "\n";

		std::cout << "** page 5,3~1 is hit\n";
		scheduler->on_schedule(page[5]); // 5, 3, 2, 1
		check_hits();
		
		std::cout << "** warning test\n";
		scheduler->off_schedule(page[0]);

		std::cout << "** page 0,5,3,2 is hit\n";
		scheduler->evict_one(); // 5, 3 ,2
		scheduler->on_schedule(page[0]); // 0, 5, 3, 2
		check_hits();

		std::cout << "** page 2,0,5,3 is hit\n";
		check_hits(); 
		scheduler->update(page[2]);

		std::cout << "** page 2,0,5 is hit\n";
		scheduler->evict_one();
		check_hits(); 
	}

	void check_hits()
	{
		for (int i = 0; i < total_size; i++)
		{
			std::cout << "page " + std::to_string(i) + " is_hit " << scheduler->is_hit(page[i]);
			std::cout << "\n";
		}
	}
};

#endif
