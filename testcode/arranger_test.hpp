#ifndef __ARRANGER_TEST_HPP__
#define __ARRANGER_TEST_HPP__

#include <iostream>

#include "../include/damemory.hpp"
#include "../include/arranger.hpp"

class Arranger_test
{
public:
	void main()
	{
		config2d c_dataset = {1, 8};
		config2d c_page = {8, 32};
		Arranger *arranger_padding = new Arranger_padding(c_dataset, c_page);
		Arranger *arranger_concatenating = new Arranger_concatenating(c_dataset, c_page);
		Arranger *arranger_hyperpadding = new Arranger_hyperpadding(c_dataset, c_page);

		std::cout << "ds_height = " << arranger_padding->get_dataset_height() << "\n";
		std::cout << "ds_width = " << arranger_padding->get_dataset_width() << "\n";
		std::cout << "page_height = " << arranger_padding->get_page_height() << "\n";
		std::cout << "page_width = " << arranger_padding->get_page_width() << "\n";

		std::cout << "\n== Padding ==\n";
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_padding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_padding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_padding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_padding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_padding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_padding);
		std::cout << "** 10 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_padding);

		std::cout << "\n== Concatenating ==\n";
		std::cout << "** 2 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_concatenating);
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_concatenating);
		std::cout << "** 4 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_concatenating);
		std::cout << "** 4 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_concatenating);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_concatenating);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_concatenating);
		std::cout << "** 7 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_concatenating);

		std::cout << "\n== Hyper-padding ==\n";
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_hyperpadding);
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_hyperpadding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_hyperpadding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_hyperpadding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_hyperpadding);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_hyperpadding);
		std::cout << "** 10 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_hyperpadding);
	}

	void num_page_for_allocation_test(int size_data, int data_width, Arranger *arranger)
	{
		std::cout << "Testing: data[" << data_width << " / " << size_data << "]\n";
		std::cout << "#data_per_page = " << arranger->get_num_w_data_per_page(size_data) << "\n";
		std::cout << "#page_per_data2d = " << arranger->get_num_w_page_per_data2d(data_width / size_data, size_data) << "\n";
	}

	void explore()
	{
		config2d c_page = {16, 64};
		for (int ds = 8; ds <= 16; ds *= 2)
		{
			config2d c_dataset = {1, ds};
			for (int round = 0; round < 3; round++)
			{
				std::cout << "round = " << round << "\n";
				Arranger *arranger;
				for (int size_data = 1; size_data <= 16; size_data++)
				{
					if (round == 0)
						arranger = new Arranger_padding(c_dataset, c_page);
					else if (round == 1)
						arranger = new Arranger_concatenating(c_dataset, c_page);
					else
						arranger = new Arranger_hyperpadding(c_dataset, c_page);

					std::cout << arranger->get_num_w_page_per_data2d(55, size_data) << ",";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
		}
		std::cout << "\n";


	}
};

#endif
