#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include "config2d.hpp"

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
		if (pages_.find(name) == pages_.end())
		{
			std::cerr << "This data named " << name << " is not exist!\n";
			return;
		}

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

	int get_size()
	{
		return pages_.size();
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

	Page_manager(int num_h, int num_w, int size_h, int size_w)
		: config_num_(num_h, num_w)
		, config_size_(size_h, size_w)
		, page_scheduler_(new Scheduler_type<Page>(config_num_.height * config_num_.width))
		, page_reposity_(page_scheduler_)
	{}

	void allocate(std::string prefix_name, int h, int w, int size_data)
	{
		// size_data is ignored now, it needs to fix later.
		const int num_row = (int)std::ceil((double)h / config_size_.height);
		const int num_col = (int)std::ceil((double)w / config_size_.width);
		const int num_total = num_row * num_col;

		for (int i = 0; i < num_total; i++)
		{
			page_reposity_.allocate(prefix_name, i);
		}
	}

	void access(std::string name)
	{
		page_reposity_.access(name);
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
};

#endif
