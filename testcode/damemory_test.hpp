#ifndef __DAMEMORY_TEST_HPP__
#define __DAMEMORY_TEST_HPP__

#include "../include/damemory.hpp"
#include "../include/page.hpp"
#include "../include/arranger.hpp"

class DAmemory_test
{
public:
	void main()
	{
		const int h_mem = 32 * 32 * 32;
		const int w_mem = 32 * 32 * 32;;
		const int h_page = 1 * 32;
		const int w_page = 4 * 32;
		const int h_dataset = 1;
		const int w_dataset = 8;

		DAmemory<Arranger_concatenating, Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);

		int matrix[64][100];

		auto mcb_matrix = damemory.allocate("matrix", 64, 100, sizeof(int));
		mcb_matrix.write(0, 0);
		mcb_matrix.write(10, 10);
		mcb_matrix.load(0, 0);

		std::cout << "matrix[64][100]\n";
		std::cout << "\n";
		damemory.report();
	}
};

#endif
