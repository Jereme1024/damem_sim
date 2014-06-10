#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

template <class Data_type>
class Matrix : public std::vector<std::vector<Data_type>>
{
public:
	Matrix (int row, int col)
		: std::vector<std::vector<Data_type>>(row, std::vector<Data_type>(col))
	{
		//std::cerr << "Matrix create " << size_row() << " " << size_col() << "\n";
	}

	inline int size_row() const
	{
		return this->size();
	}

	inline int size_col() const
	{
		return (*this)[0].size();
	}

	void show() const
	{
		std::cerr << "Matrix show (" << size_row() << ", " << size_col() << ")\n";

		for (int i = 0; i < size_row(); i++)
		{
			for (int j = 0; j < size_col(); j++)
			{
				std::cout << std::setw(2) << (*this)[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};

#endif
