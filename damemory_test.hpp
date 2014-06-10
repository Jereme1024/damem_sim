#ifndef __DAMEMORY_TEST_HPP__
#define __DAMEMORY_TEST_HPP__

#include "damemory.hpp"
#include "page.hpp"
#include "arranger.hpp"

class DAmemory_test_create
{
public:
	void main()
	{
		const int h_mem = 32 * 32 * 32;
		const int w_mem = 32 * 32 * 32;;
		const int h_page = 2 * 32;
		const int w_page = 2 * 32;
		const int h_dataset = 1;
		const int w_dataset = 8;

		DAmemory<Arranger_padding, Scheduler_LRU>(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);
	}
};

#endif
