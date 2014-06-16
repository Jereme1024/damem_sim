#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include <string>
#include <map>

#include "config2d.hpp"
#include "scheduler.hpp"

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

	void allocate(std::string prefix, int h, int w)
	{
		auto name_new = name_encoding(prefix, h, w);
		Page *page_new = new Page(name_new);

		pages_.insert(std::pair<std::string, Page *>(name_new, page_new));
	}

	void access(std::string prefix, int h, int w)
	{
		auto name = name_encoding(prefix, h, w);

		if (pages_.find(name) == pages_.end())
		{
			std::cerr << "This data named " << name << " is not exist!\n";
			return;
		}

		cnt_access_ += 1;

		if (!page_scheduler_->is_hit(pages_[name]))
		{
			if (page_scheduler_->is_full())
			{
				cnt_swap_ += 1;
			}
			page_scheduler_->on_schedule(pages_[name]);
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

	int get_size()
	{
		return pages_.size();
	}

	std::string name_encoding(std::string &prefix, int h, int w)
	{
		prefix += "." + std::to_string(h) + "," + std::to_string(w);
		return prefix;
	}
};


template <template <class> class Scheduler_type>
class Page_manager
{
private:
	config2d config_num_;

	const int num_availalbe_page_;
	Scheduler<Page> *page_scheduler_;
	Page_reposity page_reposity_;

public:
	Page_manager(config2d &config_num)
		: config_num_(config_num)
		, num_availalbe_page_(config_num.height * config_num.width)
		, page_scheduler_(new Scheduler_type<Page>(config_num.height * config_num.width))
		, page_reposity_(page_scheduler_)
	{}

	Page_manager(int num_h, int num_w)
		: config_num_(num_h, num_w)
		, num_availalbe_page_(config_num_.height * config_num_.width)
		, page_scheduler_(new Scheduler_type<Page>(config_num_.height * config_num_.width))
		, page_reposity_(page_scheduler_)
	{}

	void allocate(std::string prefix_name, int num_row, int num_col)
	{
		//const int num_total = num_row * num_col; // depredcated

		for (int r = 0; r < num_row; r++)
		{
			for (int c = 0; c < num_col; c++)
			{
				page_reposity_.allocate(prefix_name, r, c);
			}
		}
	}

	void access(std::string prefix, int h, int w)
	{
		page_reposity_.access(prefix, h, w);
	}

	int get_num_available_page()
	{
		return num_availalbe_page_;
	}

	int get_num_page()
	{
		return page_reposity_.get_size();
	}

	int get_cnt_access()
	{
		return page_reposity_.get_cnt_access();
	}

	int get_cnt_swap()
	{
		return page_reposity_.get_cnt_swap();
	}

	int get_on_schedule()
	{
		return page_scheduler_->get_size();
	}

	char *get_scheduler_name()
	{
		return page_scheduler_->get_name();
	}
};

#endif
