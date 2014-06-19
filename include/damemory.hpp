#ifndef __DAMEMORY_HPP__
#define __DAMEMORY_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>

#include "config2d.hpp"
#include "page.hpp"
#include "scheduler.hpp"
#include "arranger.hpp"

template<class Arranger_type, template <class> class Scheduler_type>
class DAmemory;

template<class Arranger_type, template <class> class Scheduler_type>
class DAmemory_control_block
{
public:
	DAmemory<Arranger_type, Scheduler_type> *damemory_;
	std::string prefix_;
	config2d config_size_;
	const int size_data_;
	
public:
	DAmemory_control_block(DAmemory<Arranger_type, Scheduler_type> *damemory, std::string prefix, int h, int w, int size_data)
		: damemory_(damemory)
		, prefix_(prefix)
		, config_size_(h, w)
		, size_data_(size_data)
	{}

	DAmemory_control_block(DAmemory_control_block &&damcb) // move constructor
		: damemory_(damcb.damemory_)
		, prefix_(damcb.prefix_)
		, config_size_(damcb.config_size_)
		, size_data_(damcb.size_data_)
	{}
	
	void write(int y, int x)
	{
		if (y >= config_size_.height || x >= config_size_.width)
		{
			std::cerr << "Out of memory access!\n";
		}

		damemory_->access(prefix_, y, x, size_data_);
	}

	void load(int y, int x)
	{
		if (y >= config_size_.height || x >= config_size_.width)
		{
			std::cerr << "Out of memory access!\n";
		}

		damemory_->access(prefix_, y, x, size_data_);
	}
};


template<class Arranger_type, template <class> class Scheduler_type>
class DAmemory
{
private:
	config2d config_da_mem_;
	config2d config_da_page_;
	config2d config_da_dataset_;
	Arranger_type arranger_;
	Page_manager<Scheduler_type> page_manager_;
	int total_data_size_;
	int cnt_dataset_access_;

	typedef DAmemory_control_block<Arranger_type, Scheduler_type> DAmcb;

public:
	DAmemory(int h_mem, int w_mem, int h_page, int w_page, int h_dataset, int w_dataset)
		: config_da_mem_(h_mem, w_mem)
		, config_da_page_(h_page, w_page)
		, config_da_dataset_(h_dataset, w_dataset)
		, arranger_(config_da_dataset_, config_da_page_)
		, page_manager_(h_mem / h_page, w_mem / w_page) // #height, #width
		, total_data_size_(0)
		, cnt_dataset_access_(0)
	{}

	DAmemory(config2d &mem, config2d &page, config2d &dataset)
		: config_da_mem_(mem)
		, config_da_page_(page)
		, config_da_dataset_(dataset)
		, arranger_(config_da_dataset_, config_da_page_)
		, page_manager_(mem.height / page.height, mem.width / page.height)
		, total_data_size_(0)
		, cnt_dataset_access_(0)
	{}

	DAmcb allocate(std::string prefix, int h, int w, int size_data)
	{
		total_data_size_ += h * w * size_data;
		
		const int num_h = arranger_.get_num_h_page_per_data2d(h, size_data);
		const int num_w = arranger_.get_num_w_page_per_data2d(w, size_data);

		page_manager_.allocate(prefix, num_h, num_w);
		
		std::cerr << "allocate page: " << num_h * num_w << "\n";
		
		return DAmcb(this, prefix, h, w, size_data);
	}

	void access(const std::string prefix, const int y, const int x, const int size_data)
	{
		const int py = get_page_y(y, size_data);
		const int px = get_page_x(x, size_data);

		page_manager_.access(prefix, py, px);
		//cnt_dataset_access_ += arranger_.get_cnt_access(y, x, size_data);
	}

	int get_page_y(const int y, const int size_data)
	{
		const int ph = arranger_.get_num_h_data_per_page(size_data);
		return (int)std::floor((double)y / ph);
	}

	int get_page_x(const int x, const int size_data)
	{
		const int pw = arranger_.get_num_w_data_per_page(size_data);
		return (int)std::floor((double)x / pw);
	}

	void report(std::string filename = "")
	{
		typedef std::pair<std::string, int> sip;
		std::vector<sip> csv_in;

		const int total_mem = config_da_mem_.height * config_da_mem_.width / 1024 / 1024;
		const int each_page = config_da_page_.height * config_da_page_.width;
		const int total_page = each_page * page_manager_.get_num_page();

		std::cout << "[ DA memory " << config_da_mem_.height << " B x " << config_da_mem_.width << " B, "
				  << total_mem * 1024 << " KB " << total_mem << " MB ]\n";
		std::cout << "= Configuration =\n";
		std::cout << "Page size: " << config_da_page_.height << " B x " << config_da_page_.width << " B\n";
		std::cout << "Dataset size: " << config_da_dataset_.height << " B x " << config_da_dataset_.width << " B\n";
		std::cout << "Arrangement policy: " << arranger_.get_name() << "\n";
		std::cout << "Schedule policy: " << page_manager_.get_scheduler_name() << "\n";

		std::cout << "= Statistics =\n";
		std::cout << "Total data allocation: " << total_data_size_ << " B\n";
		std::cout << "Total #phsical_page allocation: " << page_manager_.get_num_available_page() << "\n";
		std::cout << "Total #page allocation: " << page_manager_.get_num_page() << "\n";
		std::cout << "Memory usage (total / allocated): " << total_data_size_ << " / " << total_page
				  << ", " << ((double)total_data_size_ / total_page) << "\n";
		std::cout << "Memory access count: " << page_manager_.get_cnt_access() << "\n";
		std::cout << "Memory dataset access count: " << cnt_dataset_access_ << "\n";
		std::cout << "Memory page swap count: " << page_manager_.get_cnt_swap() << "\n";
		//std::cout << "No used pages count: " << page_manager_.get_cnt_nouse() << "\n";

		if (filename != "")
		{
			csv_in.push_back(sip("Total #phsical page", page_manager_.get_num_available_page()));
			csv_in.push_back(sip("Total #data page", page_manager_.get_num_page()));
			csv_in.push_back(sip("Total data allocation", total_data_size_));
			csv_in.push_back(sip("Memory access count", page_manager_.get_cnt_access()));
			csv_in.push_back(sip("Memory dataset access count", cnt_dataset_access_));
			csv_in.push_back(sip("Memory page swap count", page_manager_.get_cnt_swap()));
			
			csv<sip>(filename, csv_in);
		}
	}

	template <class Pair_type>
	void csv(std::string filename, std::vector<Pair_type> csv_in)
	{
		if (csv_in.size() == 0) return;

		std::ofstream csv_out(filename);
		if (csv_out.is_open() == false)
		{
			std::cerr << "csv file open failed!\n";
			return;
		}

		csv_out << csv_in[0].first;
		for (int i = 1; i < csv_in.size(); i++)
		{
			csv_out << "," << csv_in[i].first;
		}
		csv_out << "\n";

		csv_out << csv_in[0].second;
		for (int i = 1; i < csv_in.size(); i++)
		{
			csv_out << "," << csv_in[i].second;
		}
		csv_out << "\n";

		csv_out.close();
	}
};
#endif
