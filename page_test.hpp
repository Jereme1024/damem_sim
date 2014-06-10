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
		
		pm = new Page_manager<Scheduler_type>(config_num);

		show_status(pm, "initial");

		pm->allocate("test1", 1, 1);
		show_status(pm, "size += 1");

		pm->allocate("test2", 1, 1);
		show_status(pm, "size += 1");

		pm->allocate("test3", 2, 3);
		show_status(pm, "size += 6, swap += 2");

		pm->access("test3", 1, 2);
		show_status(pm, "access++");
		pm->access("test1", 0, 0);
		show_status(pm, "access++, swap++");
		pm->access("test1", 1, 1); // not exist, just test the warning
		pm->access("test999", 0, 0); // not exist, just test the warning
		show_status(pm, "values does not change");
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
