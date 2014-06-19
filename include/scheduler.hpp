#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <list>
#include <unordered_map>

template <class Struct_type>
class Scheduler
{
public:
	virtual bool is_full() = 0;
	virtual bool is_hit(Struct_type *) = 0;
	virtual void on_schedule(Struct_type *) = 0;
	virtual void off_schedule(Struct_type *) = 0;
	virtual void evict_one() = 0;
	virtual int get_size() = 0;
	virtual char *get_name() = 0;
};


template <class Struct_type>
class Scheduler_LRU : public Scheduler<Struct_type>
{
private:
	const int max_size_;
	std::list<Struct_type *> bookkeeping_; // most-LHS is most new

	typedef decltype(bookkeeping_.begin()) It_type_book;

	std::unordered_map<void *, It_type_book> lookup_bookkeeping_;

public:
	Scheduler_LRU(const int max_size)
		: max_size_(max_size)
		, bookkeeping_()
		, lookup_bookkeeping_()
	{}

	bool is_full()
	{
		return bookkeeping_.size() >= max_size_;
	}

	bool is_hit(Struct_type *page)
	{
		auto lookup = lookup_bookkeeping_.find((void *)page);
		if (lookup == lookup_bookkeeping_.end())
		{
			return false;
		}
		else
		{
			auto it = lookup->second;
			update(page, it);

			return true;
		}

		//auto it = std::find(bookkeeping_.begin(), bookkeeping_.end(), page);

		//if (it != bookkeeping_.end())
		//{
		//	update(page, it);

		//	return true;
		//}
		//else
		//{
		//	return false;
		//}
	}

	// In LRU, this will be called after is_hit(...)
	inline void update(Struct_type *page, It_type_book it)
	{
		off_schedule(it);

		new_schedule(page);
	}

	void on_schedule(Struct_type *page)
	{
		if (is_full())
		{
			evict_one();
		}

		new_schedule(page);
	}

	inline void new_schedule(Struct_type *page)
	{
		bookkeeping_.push_front(page);
		lookup_bookkeeping_.insert(std::make_pair<void *, It_type_book>((void *)page, bookkeeping_.begin()));
	}

	void off_schedule(Struct_type *page)
	{
		auto it = std::find(bookkeeping_.begin(), bookkeeping_.end(), page);
		off_schedule(it);
	}

	inline void off_schedule(It_type_book it)
	{
		lookup_bookkeeping_.erase((void *)*it);
		bookkeeping_.erase(it);
	}

	void evict_one()
	{
		auto last_one = bookkeeping_.end();
		off_schedule(--last_one);
	}

	int get_size()
	{
		return bookkeeping_.size();
	}

	char *get_name()
	{
		return (char *)"LRU";
	}
};

#endif
