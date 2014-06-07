#include <iostream>
#include <vector>
#include <iomanip>

template <class Data_type>
class Matrix : public std::vector<std::vector<Data_type>>
{
public:
	Matrix (int row, int col)
		: std::vector<std::vector<Data_type>>(row, std::vector<Data_type>(col))
	{
		std::cerr << "Matrix create " << size_row() << " " << size_col() << "\n";
	}

	void transpose(Matrix<Data_type> &mb)
	{
		std::cerr << "Matrix transpose\n";

		bool is_size_match;
		is_size_match = size_row() == mb.size_col();
		is_size_match = is_size_match && (size_col() == mb.size_row());
		
		if (!is_size_match)
		{
			std::cerr << "Matrix miss match!\n";
			exit(-1);
		}

		for (int i = 0; i < size_row(); i++)
		{
			for (int j = 0; j < size_col(); j++)
			{
				mb[j][i] = (*this)[i][j];
			}
		}
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


class Matrix_transpose_test
{
public:
	void main()
	{
		Matrix<int> m1(10, 6);
		Matrix<int> m2(6, 10);

		for (int i = 0; i < m1.size_row(); i++)
		{
			for (int j = 0; j < m1.size_col(); j++)
			{
				m1[i][j] = i * m1.size_row() + j;
			}
		}

		m1.show();

		m1.transpose(m2);

		m1.show();
		m2.show();
	}
};

int main()
{
	Matrix_transpose_test matrix_transpose_test;
	matrix_transpose_test.main();

	return 0;
}
