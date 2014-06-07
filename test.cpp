#include "damemory.hpp"
#include "damemory_test.hpp"
#include "scheduler_test.hpp"

int main()
{
	DAmemory_test_create damemory_test_create;
	damemory_test_create.main();

	Scheduler_test<Scheduler_LRU, Page> scheduler_test;
	scheduler_test.main();

	return 0;
}
