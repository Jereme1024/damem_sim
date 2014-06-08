#ifndef __PAGE_TEST_HPP__
#define __PAGE_TEST_HPP__

#include "damemory.hpp"
#include "page.hpp"

template <template <class> class Scheduler_type>
class Page_test
{
public:
	Page_manager<Scheduler_type> *pm;

	void main()
	{
		config2d config_num = {.height = 2, .width = 3};
		config2d config_size = {.height = 3, .width = 3};
		
		pm = new Page_manager<Scheduler_type>(config_num, config_size);

		show_status(pm, "initial");

		pm->allocate("test1", 3, 3, 0);
		show_status(pm, "size = 1");

		pm->allocate("test2", 1, 3, 0);
		show_status(pm, "size = 2");

		pm->allocate("test3", 6, 8, 0);
		show_status(pm, "size = 8, swap += 2");

		pm->access("test3.5");
		show_status(pm, "access++");
		pm->access("test1.0");
		show_status(pm, "access++, swap++");
		pm->access("test1.1"); // not exist
		pm->access("test999.0"); // not exist
		show_status(pm, "values no change");
	}

	void show_status(Page_manager<Scheduler_type> *pm, std::string msg)
	{
		std::cout << "** Page status: " << msg << "\n";
		std::cout << "size = " << pm->get_num_page() << "\n";
		std::cout << "access = " << pm->get_cnt_access() << "\n";
		std::cout << "swap = " << pm->get_cnt_swap() << "\n";
		std::cout << "on_schedule = " << pm->get_on_schedule() << "\n";
	}

};

#endif
