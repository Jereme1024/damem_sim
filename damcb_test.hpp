#ifndef __DAMCB_TEST_HPP__
#define __DAMCB_TEST_HPP__

#include "damemory.hpp"
#include "page.hpp"

class DAmemory_control_block_test
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

		DAmemory<Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);

		int matrix[20][10];

		auto mcb_matrix = damemory.allocate<int>("matrix", 20, 10);
		mcb_matrix.write(20, 10);
		mcb_matrix.load(10, 10);
	}
};

#endif
