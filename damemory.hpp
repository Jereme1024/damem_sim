#ifndef __DAMEMORY_HPP__
#define __DAMEMORY_HPP__

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>

#include "scheduler.hpp"

struct config2d
{
	const int height;
	const int width;

	config2d(const int h, const int w) : height(h), width(w)
	{}

	config2d(config2d &c) : height(c.height), width(c.width)
	{}
};


struct Page
{
	std::string name_;

	Page(std::string name)
		: name_(name)
	{}


	~Page()
	{
		std::cerr << "Page destructer!";
	}
};


class Page_reposity
{
private:
	std::map<std::string, Page *> pages_;
	Scheduler<Page> *page_scheduler_;
	int cnt_access_;
	int cnt_swap_;

public:
	Page_reposity(Scheduler<Page> *page_scheduler)
		: pages_()
		, page_scheduler_(page_scheduler)
		, cnt_access_(0)
		, cnt_swap_(0)
	{}

	void allocate(std::string prefix, int index)
	{
		std::string name_new = prefix + "." + std::to_string(index);
		Page *page_new = new Page(name_new);

		pages_.insert(std::pair<std::string, Page *>(name_new, page_new));
		if (!page_scheduler_->is_full())
		{
			page_scheduler_->on_schedule(page_new);
		} else {
			page_scheduler_->evict_one();
			page_scheduler_->on_schedule(page_new);
			cnt_swap_ += 1;
		}
	}

	void access(std::string name)
	{
		cnt_access_ += 1;

		if (page_scheduler_->is_hit(pages_[name]))
		{
			page_scheduler_->update(pages_[name]);
		} else {
			page_scheduler_->evict_one();
			page_scheduler_->on_schedule(pages_[name]);

			cnt_swap_ += 1;
		}
	}

	int get_cnt_access()
	{
		return cnt_access_;
	}

	int get_cnt_swap()
	{
		return cnt_swap_;
	}
};


template <template <class> class Scheduler_type>
class Page_manager
{
private:
	config2d config_num_;
	config2d config_size_;

	Scheduler<Page> *page_scheduler_;
	Page_reposity page_reposity_;

public:
	Page_manager(config2d &config_num, config2d &config_size)
		: config_num_(config_num)
		, config_size_(config_size)
		, page_scheduler_(new Scheduler_type<Page>(config_num.height * config_num.width))
		, page_reposity_(page_scheduler_)
	{}

	void allocate(std::string prefix_name, int h, int w, int size_data)
	{
		const int num_row = config_size_.height / h;
		const int num_col = config_size_.width / w;
		const int num_total = num_row * num_col;

		for (int i = 0; i < num_total; i++)
		{
			page_reposity_.allocate(prefix_name, i);
		}
	}
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

};
#endif
