#include "damemory.hpp"
#include "damemory_test.hpp"
#include "scheduler_test.hpp"
#include "page_test.hpp"

int main()
{
	std::cout << "[ DA memory test driver ]\n";
	DAmemory_test_create damemory_test_create;
	damemory_test_create.main();

	std::cout << "[ Scheduler test driver ]\n";
	Scheduler_test<Scheduler_LRU, Page> scheduler_test;
	scheduler_test.main();

	std::cout << "[ Page test driver ]\n";
	Page_test<Scheduler_LRU> page_test;
	page_test.main();

	return 0;
}
