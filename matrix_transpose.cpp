#include <iostream>
#include <vector>
#include <iomanip>

#include "include/matrix.hpp"
#include "include/damemory.hpp"


template <class Data_type>
void transpose(Matrix<Data_type> &ma, Matrix<Data_type> &mb)
{
	// DA memory create
	const int h_mem = 1 * 32 * 32;
	const int w_mem = 1 * 32 * 32;;
	const int h_page = 1 * 16;
	const int w_page = 4 * 32;
	const int h_dataset = 1;
	const int w_dataset = 8;

	DAmemory<Arranger_padding, Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);

	// DA memory control block allocate
	auto mcb_ma = damemory.allocate("ma", ma.size_row(), ma.size_col(), sizeof(Data_type));
	auto mcb_mb = damemory.allocate("mb", mb.size_row(), mb.size_col(), sizeof(Data_type));

	// Transpose start
	bool is_size_match;
	is_size_match = ma.size_row() == mb.size_col();
	is_size_match = is_size_match && (ma.size_col() == mb.size_row());
	
	if (!is_size_match)
	{
		std::cerr << "Matrix miss match!\n";
		exit(-1);
	}

	for (int i = 0; i < ma.size_row(); i++)
	{
		for (int j = 0; j < ma.size_col(); j++)
		{
			mb[j][i] = ma[i][j];
			mcb_ma.load(i, j);
			mcb_mb.write(j, i);
		}
	}

	damemory.report("matrix_transpose.csv");
}

int main()
{
	Matrix<int> m1(1000, 1000);
	Matrix<int> m2(1000, 1000);

	for (int i = 0; i < m1.size_row(); i++)
	{
		for (int j = 0; j < m1.size_col(); j++)
		{
			m1[i][j] = i * m1.size_row() + j;
		}
	}

	transpose(m1, m2);

	return 0;
}
