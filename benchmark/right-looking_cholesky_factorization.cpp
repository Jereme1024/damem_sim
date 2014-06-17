#include "magic-instruction.h"
#include <stdio.h>
#include <stdlib.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define WIDTH 10
//#define MAX 5
//#define PRINT

#include "include/damemory.hpp"

int main()
{
	// DA memory create
	const int h_mem = 1 * 8 * 32;
	const int w_mem = 8 * 8 * 32;
	const int h_page = 1 * 8;
	const int w_page = 8 * 8;
	const int h_dataset = 1;
	const int w_dataset = 8;

	// POLICY = (Arranger_padding | Arranger_concatenating | Arranger_hyperpadding)
	DAmemory<POLICY, Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);

	int i, j, k;
	float I;
	float *A;
	//FILE *ofile;
	//printf("&i: %p\t&j: %p\t&k: %p\t&I: %p\n", &i, &j, &k, &I);
	//printf("&a: %p\n", &A);
	//printf("transaction\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", WIDTH, WIDTH, MAX);
/////////////// malloc
	A = (float *)malloc(WIDTH*WIDTH*sizeof(float));
	auto m_a = damemory.allocate("a", WIDTH, WIDTH, sizeof(float));
	if (!A)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", A, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", A, WIDTH, WIDTH);
	//fflush(ofile);
	//fclose(ofile);
/////////////// declare register variable
	//ofile = fopen(REGISTER_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", REGISTER_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p\n", &i);
	//fprintf(ofile, "%p\n", &j);
	//fprintf(ofile, "%p\n", &k);
	//fprintf(ofile, "%p\n", &I);
	//fprintf(ofile, "%p\n", &A);
	//fflush(ofile);
	//fclose(ofile);
/////////////// initialization
	for (i=0; i<WIDTH; i++)
		for (j=0; j<WIDTH; j++)
		{
			A[i*WIDTH+j] = i<j ? i+1 : j+1;
		}
/////////////// print result
#ifdef PRINT
	printf("test case: \n");
	for (i=0; i<WIDTH; i++)
	{
		for (j=0; j<WIDTH; j++)
			printf("%f ", A[i*WIDTH+j]);
		printf("\n");
	}
#endif
/////////////// right-looking cholesky factorization
	MAGIC(3);
	for (j=0; j<WIDTH; j++)
	{
		MAGIC(1);
//		A[j*WIDTH+j] = A[j*WIDTH+j] * A[j*WIDTH+j];
		I = A[j*WIDTH+j];
		m_a.load(j, j);
		A[j*WIDTH+j] = I * I;
		m_a.write(j, j);
		MAGIC(1);
		MAGIC(2);
		for (i=j+1; i<WIDTH; i++)
		{
			A[i*WIDTH+j] = A[i*WIDTH+j] / A[j*WIDTH+j];
			m_a.load(i, j);
			m_a.load(j, j);
			m_a.write(i, j);
		}
		MAGIC(2);
		for (i=j+1; i<WIDTH; i++)
			for (k=j+1; k<=i; k++)
			{
				MAGIC(2);
				I = A[i*WIDTH+j] * A[k*WIDTH+j];
				m_a.load(i, j);
				m_a.load(k, j);
				MAGIC(2);
				MAGIC(1);
				A[i*WIDTH+k] -= I;
				m_a.write(i, k);
				MAGIC(1);
//				A[i*WIDTH+k] = A[i*WIDTH+k] - A[i*WIDTH+j] * A[k*WIDTH+j];
			}
	}
	MAGIC(3);
/////////////// print result
#ifdef PRINT
	printf("result: \n");
	for (j=0; j<WIDTH; j++)
		for (i=j; i<WIDTH; i++)
			for (k=i+1; k<WIDTH; k++)
				A[i*WIDTH+k] = 0;
	for (i=0; i<WIDTH; i++)
	{
		for (j=0; j<WIDTH; j++)
			printf("%f ", A[i*WIDTH+j]);
		printf("\n");
	}
#endif
/////////////// free
	free(A);
	damemory.report("right.csv");
	return 0;
}

