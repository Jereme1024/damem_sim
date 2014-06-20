#ifndef __ARRANGER_HPP__
#define __ARRANGER_HPP__

#include <cmath>

#include "config2d.hpp"

class Arranger
{
private:
	config2d config_dataset_;
	config2d config_page_;

public:
	Arranger(config2d &c_dataset, config2d &c_page)
		: config_dataset_(c_dataset)
		, config_page_(c_page)
	{}

	Arranger()
		: config_dataset_(0, 0)
		, config_page_(0, 0)
	{}

	void set_config_dataset(config2d c_dataset)
	{
		config_dataset_ = c_dataset;
	}

	void set_config_page(config2d c_page)
	{
		config_page_ = c_page;
	}

	int get_dataset_height() const
	{
		return config_dataset_.height;
	}

	int get_dataset_width() const
	{
		return config_dataset_.width;
	}

	int get_page_height() const
	{
		return config_page_.height;
	}

	int get_page_width() const
	{
		return config_page_.width;
	}

	int get_num_dataset_per_page() const
	{
		return get_page_width() / get_dataset_width();
	}

	int get_num_w_page_per_data2d(int w, int size_data)
	{
		return (int)std::ceil((double)w / get_num_w_data_per_page(size_data));
	}

	int get_num_h_page_per_data2d(int h, int size_data)
	{
		return (int)std::ceil((double)h / get_page_height());
	}

	int get_num_h_data_per_page(int size_data)
	{
		return get_page_height() / get_dataset_height();
	}

	virtual int get_num_w_data_per_page(int size_data) = 0;
	virtual int get_cnt_access(int y, int x, int size_data) = 0;
	virtual char *get_name() = 0;
	//virtual int get_dataset_base(int y, int x, int size_data) = 0;
	//virtual int get_dataset_offset(int y, int x, int size_data) = 0;
};

class Arranger_padding : public Arranger
{
public:
	Arranger_padding(config2d &c_dataset, config2d &c_page)
		: Arranger(c_dataset, c_page)
	{}

	Arranger_padding()
		: Arranger()
	{}

	int get_num_w_data_per_page(int size_data)
	{
		const int num_dataset_per_data = (int)std::ceil((double)size_data / get_dataset_width());
		const int num_data_per_page =  (int)std::floor((double)get_num_dataset_per_page() / num_dataset_per_data);
		return num_data_per_page;
	}

	int get_cnt_access(int y, int x, int size_data)
	{
		const int cnt_access = (int)std::ceil((double)size_data / get_dataset_width());
		return cnt_access;
	}

	char *get_name()
	{
		return (char *)"padding";
	}
};

class Arranger_concatenating : public Arranger
{
public:
	Arranger_concatenating(config2d &c_dataset, config2d &c_page)
		: Arranger(c_dataset, c_page)
	{}

	Arranger_concatenating()
		: Arranger()
	{}

	int get_num_w_data_per_page(int size_data)
	{
		const int num_data_per_page = (int)std::floor((double)get_page_width() / size_data);
		return num_data_per_page;
	}

	int get_cnt_access(int y, int x, int size_data)
	{
		//const int cnt_access = (int)std::ceil((double)size_data / get_dataset_width());
		
		int offset_in_a_page = x % get_num_w_data_per_page(size_data);
		int byte_start = offset_in_a_page * size_data;
		int byte_end = byte_start + (size_data - 1);

		int ds_start = byte_start / get_dataset_width();
		int ds_end = byte_end / get_dataset_width();

		const int cnt_access = ds_end - ds_start + 1;
		
		return cnt_access;
	}

	char *get_name()
	{
		return (char *)"concatenating";
	}
};

class Arranger_hyperpadding : public Arranger
{
public:
	Arranger_hyperpadding(config2d &c_dataset, config2d &c_page)
		: Arranger(c_dataset, c_page)
	{}

	Arranger_hyperpadding()
		: Arranger()
	{}

	int get_num_w_data_per_page(int size_data)
	{
		if (size_data <= get_dataset_width())
		{
			const double num_data_per_dataset = std::floor((double)get_dataset_width() / size_data);
			const int num_data_per_page = num_data_per_dataset * get_num_dataset_per_page();
			return num_data_per_page;
		}
		else
		{
			const double num_dataset_per_data = std::ceil((double)size_data / get_dataset_width());
			const int num_data_per_page = (int)std::floor((double)get_num_dataset_per_page() / num_dataset_per_data);
			return num_data_per_page;
		}
	}

	int get_cnt_access(int y, int x, int size_data)
	{
		const int cnt_access = (int)std::ceil((double)size_data / get_dataset_width());
		return cnt_access;
	}

	char *get_name()
	{
		return (char *)"hyperpadding";
	}
};

class Arranger_one_dim : public Arranger_concatenating
{
public:
	Arranger_one_dim(config2d &c_dataset, config2d &c_page)
		: Arranger_concatenating(c_dataset, c_page)
	{}

	Arranger_one_dim()
		: Arranger_concatenating()
	{}

	char *get_name()
	{
		return (char *)"one_dim";
	}
};

#endif
