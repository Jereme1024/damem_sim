#ifndef __ARRANGER_TEST_HPP__
#define __ARRANGER_TEST_HPP__

#include <iostream>
#include <cassert>
#include <fstream>

#include "../include/damemory.hpp"
#include "../include/arranger.hpp"

class Arranger_test
{
public:
	void main()
	{
		config2d c_dataset = {1, 8};
		config2d c_page = {8, 64};

		Arranger *arranger_padding = new Arranger_padding(c_dataset, c_page);
		Arranger *arranger_concatenating = new Arranger_concatenating(c_dataset, c_page);
		Arranger *arranger_hyperpadding = new Arranger_hyperpadding(c_dataset, c_page);
		Arranger *arranger_one_dim = new Arranger_one_dim(c_dataset, c_page);

		std::cout << "ds_height = " << arranger_padding->get_dataset_height() << "\n";
		std::cout << "ds_width = " << arranger_padding->get_dataset_width() << "\n";
		std::cout << "page_height = " << arranger_padding->get_page_height() << "\n";
		std::cout << "page_width = " << arranger_padding->get_page_width() << "\n";

		// {[8][8][8][8]} each row, eight row totally
		//
		// padding
		// size_data 3 (0, 2) in 0 page 3 ds 1 access
		dataset_access_count_test(0, 2, 3, arranger_padding, 1);
		// size_data 4 (0, 2) in 0 page 3 ds 1 access
		dataset_access_count_test(0, 2, 4, arranger_padding, 1);
		// size_data 8 (0, 2) in 0 page 3 ds 1 access
		dataset_access_count_test(0, 2, 8, arranger_padding, 1);
		// size_data 9 (0, 2) in 1 page 0 ds 2 access
		dataset_access_count_test(0, 2, 9, arranger_padding, 2);
		// size_data 9 (0, 7) in 3 page 1 ds 2 access
		dataset_access_count_test(0, 7, 9, arranger_padding, 2);
		// size_data 17 (0, 2) in 2 page 0 ds 3 access
		dataset_access_count_test(0, 2, 17, arranger_padding, 3);

		// {[8][8][8][8]} each row, eight row totally
		//
		// concatenating
		// size_data 3 (0, 2) in 0 page 0 ds 2 access
		dataset_access_count_test(0, 2, 3, arranger_concatenating, 2);
		// size_data 4 (0, 2) in 0 page 1 ds 1 access
		dataset_access_count_test(0, 2, 4, arranger_concatenating, 1);
		// size_data 8 (0, 2) in 0 page 2 ds 1 access
		dataset_access_count_test(0, 2, 8, arranger_concatenating, 1);
		// size_data 9 (0, 2) in 0 page 3 ds 2 access
		dataset_access_count_test(0, 2, 9, arranger_concatenating, 2);
		// size_data 9 (0, 7) in 2 page 1 ds 2 access
		dataset_access_count_test(0, 7, 9, arranger_concatenating, 2);
		// size_data 17 (0, 2) in 2 page 0 ds 3 access
		dataset_access_count_test(0, 2, 17, arranger_concatenating, 3);

		// {[8][8][8][8]} each row, eight row totally
		//
		// one_dim
		// size_data 3 (0, 2) in 0 page 0 ds 2 access
		dataset_access_count_test(0, 2, 3, arranger_one_dim, 2);
		// size_data 4 (0, 2) in 0 page 1 ds 1 access
		dataset_access_count_test(0, 2, 4, arranger_one_dim, 1);
		// size_data 8 (0, 2) in 0 page 2 ds 1 access
		dataset_access_count_test(0, 2, 8, arranger_one_dim, 1);
		// size_data 9 (0, 2) in 0 page 3 ds 2 access
		dataset_access_count_test(0, 2, 9, arranger_one_dim, 2);
		// size_data 9 (0, 7) in 2 page 1 ds 2 access
		dataset_access_count_test(0, 7, 9, arranger_one_dim, 2);
		// size_data 17 (0, 2) in 2 page 0 ds 3 access
		dataset_access_count_test(0, 2, 17, arranger_one_dim, 3);

		// {[8][8][8][8]} each row, eight row totally
		//
		// hyperpadding
		// size_data 3 (0, 2) in 0 page 1 ds 1 access
		dataset_access_count_test(0, 2, 3, arranger_hyperpadding, 1);
		// size_data 4 (0, 2) in 0 page 1 ds 1 access
		dataset_access_count_test(0, 2, 4, arranger_hyperpadding, 1);
		// size_data 8 (0, 2) in 0 page 2 ds 1 access
		dataset_access_count_test(0, 2, 8, arranger_hyperpadding, 1);
		// size_data 9 (0, 2) in 1 page 0 ds 2 access
		dataset_access_count_test(0, 2, 9, arranger_hyperpadding, 2);
		// size_data 9 (0, 7) in 3 page 1 ds 2 access
		dataset_access_count_test(0, 7, 9, arranger_hyperpadding, 2);
		// size_data 17 (0, 2) in 2 page 0 ds 3 access
		dataset_access_count_test(0, 2, 17, arranger_hyperpadding, 3);


		std::cout << "\n== Padding ==\n";
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_padding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_padding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_padding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_padding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_padding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_padding, 5);
		std::cout << "** 10 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_padding, 10);

		std::cout << "\n== Concatenating ==\n";
		std::cout << "** 2 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_concatenating, 2);
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_concatenating, 3);
		std::cout << "** 4 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_concatenating, 4);
		std::cout << "** 4 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_concatenating, 4);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_concatenating, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_concatenating, 5);
		std::cout << "** 7 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_concatenating, 7);

		std::cout << "\n== Hyper-padding ==\n";
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(3, 3 * 19, arranger_hyperpadding, 3);
		std::cout << "** 3 pages needed\n";
		num_page_for_allocation_test(4, 4 * 19, arranger_hyperpadding, 3);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(5, 5 * 19, arranger_hyperpadding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(6, 6 * 19, arranger_hyperpadding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(7, 7 * 19, arranger_hyperpadding, 5);
		std::cout << "** 5 pages needed\n";
		num_page_for_allocation_test(8, 8 * 19, arranger_hyperpadding, 5);
		std::cout << "** 10 pages needed\n";
		num_page_for_allocation_test(9, 9 * 19, arranger_hyperpadding, 10);
	}

	void num_page_for_allocation_test(int size_data, int data_width, Arranger *arranger, int answer)
	{
		std::cout << "Testing: data[" << data_width << " / " << size_data << "]\n";
		std::cout << "#data_per_page = " << arranger->get_num_w_data_per_page(size_data) << "\n";
		int test = arranger->get_num_w_page_per_data2d(data_width / size_data, size_data);
		assert (test == answer);
		std::cout << "#page_per_data2d = " << test << "...PASS\n";
	}

	void dataset_access_count_test(int y, int x, int size_data, Arranger *arranger, int answer)
	{
		int test = arranger->get_cnt_access(y, x, size_data);
		assert (test == answer);
		std::cout << "#access = " << arranger->get_cnt_access(y, x, size_data) << "...PASS \n";
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

	void explore_pw(std::string filename = "explore_pw.csv")
	{
		//config2d c_page = {1, 128};
		config2d c_page = {1, 64};

		Arranger *arranger[3];
		arranger[0] = new Arranger_padding();
		arranger[1] = new Arranger_concatenating();
		arranger[2] = new Arranger_hyperpadding();

		std::ofstream csv_out(filename);
		if (csv_out.is_open() == false)
		{
			std::cerr << "Csv file open failed!\n";
			exit(-1);
		}

		const int test_time = 100;
		const int max_data = 32;

		csv_out << "policy,p_w";
		for (int size_data = 1; size_data <= max_data; size_data++)
		{
			csv_out << "," << size_data;
		}
		csv_out << "\n";

		std::vector<int> size_dataset = {2, 4, 8, 16, 32};
		for (int ds = 0; ds < size_dataset.size(); ds++)
		{
			//std::cout << "[[ " << arranger[a]->get_name() << " dataset size: " << size_dataset[ds] << " ]]\n";
			for (int a = 0; a < 3; a++)
			{
				csv_out << arranger[a]->get_name();
				csv_out << "," << size_dataset[ds];

				config2d c_dataset = {1, size_dataset[ds]};
				arranger[a]->set_config_page(c_page);
				arranger[a]->set_config_dataset(c_dataset);

				for (int size_data = 1; size_data <= max_data; size_data++)
				{
					//std::cout << arranger[a]->get_name() << " avg : " << avg_cnt_access << "\n";
					csv_out << "," << arranger[a]->get_num_w_data_per_page(size_data);
 
				}
				csv_out << "\n";
			}
		}

		csv_out.close();
	}

	void explore_ds_access(std::string filename = "explore_ds.csv")
	{
		config2d c_page = {1, 4096};

		Arranger *arranger[3];
		arranger[0] = new Arranger_padding();
		arranger[1] = new Arranger_concatenating();
		arranger[2] = new Arranger_hyperpadding();

		std::ofstream csv_out(filename);
		if (csv_out.is_open() == false)
		{
			std::cerr << "Csv file open failed!\n";
			exit(-1);
		}

		const int test_time = 100;
		const int max_data = 32;

		csv_out << "policy,dataset";
		for (int size_data = 1; size_data <= max_data; size_data++)
		{
			csv_out << "," << size_data;
		}
		csv_out << "\n";

		std::vector<int> size_dataset = {2, 4, 8, 16, 32};
		for (int ds = 0; ds < size_dataset.size(); ds++)
		{
			//std::cout << "[[ " << arranger[a]->get_name() << " dataset size: " << size_dataset[ds] << " ]]\n";
			for (int a = 0; a < 3; a++)
			{
				csv_out << arranger[a]->get_name();
				csv_out << "," << size_dataset[ds];

				config2d c_dataset = {1, size_dataset[ds]};
				arranger[a]->set_config_page(c_page);
				arranger[a]->set_config_dataset(c_dataset);

				for (int size_data = 1; size_data <= max_data; size_data++)
				{
					int cnt_access = 0;
					//std::cout << "[ data size: " << size_data << " ]\n";

					for (int i = 0; i < test_time; i++)
						cnt_access += arranger[a]->get_cnt_access(0, i, size_data);

					double avg_cnt_access = (double)cnt_access / test_time;
					//std::cout << arranger[a]->get_name() << " avg : " << avg_cnt_access << "\n";
					csv_out << "," << avg_cnt_access;
				}
				csv_out << "\n";
			}
		}

		csv_out.close();
	}
};

#endif
