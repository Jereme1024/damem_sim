#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

template <class Struct_type>
class Scheduler
{
public:

	virtual bool is_full() = 0;
	virtual bool is_hit(Struct_type *) = 0;
	virtual void update(Struct_type *) = 0;
	virtual void on_schedule(Struct_type *) = 0;
	virtual void off_schedule(Struct_type *) = 0;
	virtual void evict_one() = 0;
	virtual int get_size() = 0;
};


template <class Struct_type>
class Scheduler_LRU : public Scheduler<Struct_type>
{
private:
	const int max_size_;
	std::list<Struct_type *> bookkeeping_; // most-LHS is most new

public:
	Scheduler_LRU(const int max_size)
		: max_size_(max_size)
		, bookkeeping_()
	{}

	bool is_full()
	{
		return bookkeeping_.size() >= max_size_;
	}

	bool is_hit(Struct_type *page)
	{
		auto it = std::find(bookkeeping_.begin(), bookkeeping_.end(), page);
		return it != bookkeeping_.end();
	}

	void update(Struct_type *page)
	{
		if (!is_hit(page))
		{
			std::cerr << "Scheduler update bug warning/occur!\n";
			return;
		}

		bookkeeping_.remove(page);
		bookkeeping_.push_front(page);
	}

	void on_schedule(Struct_type *page)
	{
		bookkeeping_.push_front(page);
	}

	void off_schedule(Struct_type *page)
	{
		if (!is_hit(page))
			std::cerr << "Scheduler off_schedule bug warning/occur!\n";

		bookkeeping_.remove(page);
	}

	void evict_one()
	{
		bookkeeping_.pop_back();
	}

	int get_size()
	{
		return bookkeeping_.size();
	}
};

#endif
