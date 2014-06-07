#ifndef __DAMEMORY_HPP__
#define __DAMEMORY_HPP__

#include <iostream>
#include <vector>
#include <list>

struct config2d
{
	const int height;
	const int width;

	config2d(const int h, const int w) : height(h), width(w)
	{}
};


struct Page
{
	std::string name_;
	bool is_online_;

	Page(std::string name, bool is_online)
		: name_(name)
		, is_online_(is_online)
	{}
};


class Page_manager
{
private:
	config2d config_da_page;

	std::list<Page> online;
	std::list<Page> offline;

public:
	Page_manager(config2d &config)
		: config_da_page(config)
	{}

	
};


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


class DAmemory
{
private:
	config2d config_da_mem;
	config2d config_da_page;
	config2d config_da_dataset;

public:
	DAmemory(int h_mem, int w_mem, int h_page, int w_page, int h_dataset, int w_dataset)
		: config_da_mem(h_mem, w_mem)
		, config_da_page(h_page, w_page)
		, config_da_dataset(h_dataset, w_dataset)
	{
		std::cerr << "DA memory create\n";
		std::cerr << "da memory h = " << config_da_mem.height << " w = " << config_da_mem.width << "\n";
		std::cerr << "da page h = " << config_da_page.height << " w = " << config_da_page.width << "\n";
		std::cerr << "da dataset h = " << config_da_dataset.height << " w = " << config_da_dataset.width << "\n";
	}

	void allocate(...)
	{
	}

	void free(...)
	{
	}
};
#endif
