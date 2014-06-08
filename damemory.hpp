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
#include "scheduler.hpp"
#include "page.hpp"

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

template<template <class> class Scheduler_type>
class DAmemory;

template<template <class> class Scheduler_type>
class DAmemory_control_block
{
public:
	DAmemory<Scheduler_type> *damemory_;
	std::string prefix_;
	config2d config_size_;
	int data_size_;
	

public:
	DAmemory_control_block(DAmemory<Scheduler_type> *damemory, std::string prefix, int h, int w, int data_size)
		: damemory_(damemory)
		, prefix_(prefix)
		, config_size_(h, w)
		, data_size_(data_size)
	{}

	DAmemory_control_block(DAmemory_control_block &&damcb)
		: damemory_(damcb.damemory_)
		, prefix_(damcb.prefix_)
		, config_size_(damcb.config_size_)
		, data_size_(damcb.data_size_)
	{}
	
	void write(int y, int x)
	{
		std::cout << "write data[" << y << "][" << x << "]\n";
		damemory_->access(this, prefix_, y, x);
	}

	void load(int y, int x)
	{
		std::cout << "load data[" << y << "][" << x << "]\n";
		damemory_->access(this, prefix_, y, x);
	}
};


template<template <class> class Scheduler_type>
class DAmemory
{
private:
	config2d config_da_mem;
	config2d config_da_page;
	config2d config_da_dataset;
	Page_manager<Scheduler_type> page_manager_;

	typedef DAmemory_control_block<Scheduler_type> DAmcb;

public:
	DAmemory(int h_mem, int w_mem, int h_page, int w_page, int h_dataset, int w_dataset)
		: config_da_mem(h_mem, w_mem)
		, config_da_page(h_page, w_page)
		, config_da_dataset(h_dataset, w_dataset)
		, page_manager_(3, 2, 3, 3)
	{
		std::cerr << "DA memory create\n";
		std::cerr << "da memory h = " << config_da_mem.height << " w = " << config_da_mem.width << "\n";
		std::cerr << "da page h = " << config_da_page.height << " w = " << config_da_page.width << "\n";
		std::cerr << "da dataset h = " << config_da_dataset.height << " w = " << config_da_dataset.width << "\n";
	}

	template <class Data_type>
	DAmcb allocate(std::string prefix, int h, int w)
	{
		std::cout << "allocate a data having size = " << sizeof(Data_type)
				  << " with h = " << h << " w = " << w << "\n";

		return DAmcb(this, prefix, h, w, sizeof(Data_type));
	}

	void access(DAmcb *damcb, std::string prefix, int y, int x)
	{
		std::cout << "DAmemory access " << prefix << "[" << y << "][" << x << "]\n";

		int dataset_h = 1;
		int dataset_w = 8;

		int page_w = 9; 
		int page_h = 9; 

		// using padding policy
		// how many dataset in one page
		int num_ds_w = std::floor((double)page_w / dataset_w); // page_w is larger than dataset_w for surely

		// how many dataset needed for a data
		int num_data_w = std::ceil((double)damcb->data_size_ / dataset_w);

		int index_y = y / page_h;
		int index_x = x * num_data_w  / num_ds_w;

		std::cout << "DAmemory access " << prefix << " in page " << index_y << ", " << index_y << "\n";
	}

};
#endif
