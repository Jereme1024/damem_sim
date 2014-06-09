#include <iostream>

#include "config2d_test.hpp"
#include "damemory.hpp"
#include "damemory_test.hpp"
#include "scheduler_test.hpp"
#include "page_test.hpp"
#include "damcb_test.hpp"
#include "arranger_test.hpp"

int main()
{
	std::cout << "\n[ Config 2D test driver ]\n";
	Config2d_test config2d_test;
	config2d_test.main();

	std::cout << "\n[ DA memory test driver ]\n";
	DAmemory_test_create damemory_test_create;
	damemory_test_create.main();

	std::cout << "\n[ Scheduler test driver ]\n";
	Scheduler_test<Scheduler_LRU, Page> scheduler_test;
	scheduler_test.main();

	std::cout << "\n[ Page test driver ]\n";
	Page_test<Scheduler_LRU> page_test;
	page_test.main();

	std::cout << "\n[ DA memory control block test driver ]\n";
	DAmemory_control_block_test mcb_test;
	mcb_test.main();

	std::cout << "\n[ Arranger test driver ]\n";
	Arranger_test arranger;
	arranger.main();

	return 0;
}
