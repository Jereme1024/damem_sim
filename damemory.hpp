#ifndef __DAMEMORY_HPP__
#define __DAMEMORY_HPP__

#include <iostream>
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

template <class Data_type>
class Dataset_manager
{
private:
	config2d config_da_dataset;
	int cnt_access;

public:
	Dataset_manager(config2d &config) 
		: config_da_dataset(config)
		, cnt_access(0)
	{}

	void access(int row, int col)
	{
		std::cerr << "This data needs " << access_calc() << " access\n";
		cnt_access += access_calc();
	}

	int access_calc(int row, int col)
	{
		return 1;
	}
};

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
		std::cout << "write data[" << y << "][" << x << "]\n";

		if (y >= config_size_.height || x >= config_size_.width)
		{
			std::cerr << "Out of memory access!\n";
		}

		damemory_->access(prefix_, y, x, size_data_);
	}

	void load(int y, int x)
	{
		std::cout << "load data[" << y << "][" << x << "]\n";

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

	typedef DAmemory_control_block<Arranger_type, Scheduler_type> DAmcb;

public:
	DAmemory(int h_mem, int w_mem, int h_page, int w_page, int h_dataset, int w_dataset)
		: config_da_mem_(h_mem, w_mem)
		, config_da_page_(h_page, w_page)
		, config_da_dataset_(h_dataset, w_dataset)
		, arranger_(config_da_dataset_, config_da_page_)
		, page_manager_(h_page / h_dataset, w_page / w_dataset) // #height, #width
		, total_data_size_(0)
	{}

	DAmemory(config2d &mem, config2d &page, config2d &dataset)
		: config_da_mem_(mem)
		, config_da_page_(page)
		, config_da_dataset_(dataset)
		, arranger_(config_da_dataset_, config_da_page_)
		, page_manager_(page.height / dataset.height, page.width / dataset.height) // #height, #width
		, total_data_size_(0)
	{}

	DAmcb allocate(std::string prefix, int h, int w, int size_data)
	{
		std::cout << "allocate a data having size = " << size_data
				  << " with h = " << h << " w = " << w << "\n";

		total_data_size_ += h * w;
		
		const int num_h = arranger_.get_num_h_page_per_data2d(h, size_data);
		const int num_w = arranger_.get_num_w_page_per_data2d(w, size_data);

		page_manager_.allocate(prefix, num_h, num_w);
		
		return DAmcb(this, prefix, h, w, size_data);
	}

	void access(const std::string prefix, const int y, const int x, const int size_data)
	{
		const int py = get_page_y(y, size_data);
		const int px = get_page_x(x, size_data);

		std::cout << "DAmemory access " << prefix << " in page " << py << ", " << px << "\n";

		page_manager_.access(prefix, py, px);
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
};
#endif
