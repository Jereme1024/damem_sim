#include "magic-instruction.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define MAX 10
//#define WIDTH 3
//#define PRINT

#include "include/damemory.hpp"

int main()
{
	// DA memory create
	const int h_mem = 1 * 16 * 32;
	const int w_mem = 1 * 16 * 32;
	const int h_page = 1 * 16;
	const int w_page = 4 * 16;
	const int h_dataset = 1;
	const int w_dataset = 8;

	// POLICY = (Arranger_padding | Arranger_concatenating | Arranger_hyperpadding)
	DAmemory<POLICY, Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);
	int i, j;
	int m, n;
	int I;
	int *A, *B;
	//FILE *ofile;
	m = n = WIDTH;
	//printf("&i: %p\t&j: %p\t&I: %p\t&m: %p\t&n: %p\n", &i, &j, &I, &m, &n);
	//printf("&A: %p\t&B: %p\n", &A, &B);
	//printf("transaction\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", m, n, MAX);
/////////////// malloc
	A = (int *)malloc(m*n*sizeof(int));
	auto m_a = damemory.allocate("a", m, n, sizeof(int));
	B = (int *)malloc(m*n*sizeof(int));
	auto m_b = damemory.allocate("b", m, n, sizeof(int));
	if (!A || !B)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", A, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", B, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", A, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", B, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &I);
	//fprintf(ofile, "%p\n", &A);
	//fprintf(ofile, "%p\n", &B);
	//fflush(ofile);
	//fclose(ofile);
//	system("umount /host");
/////////////// initialization
	srand(time(0));
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
		{
			if (m!=n || WIDTH!=m)
			{
				printf("WIDTH: %d\tm: %d\tn: %d\n", WIDTH, m, n);
				exit(1);
			}
			I = rand()%(MAX+1);
			A[i*WIDTH+j] = I;	// currently no surport write
		}
/////////////// transpose
	MAGIC(3);
	for (i=0; i<WIDTH; i++)
		for (j=0; j<WIDTH; j++)
		{
			MAGIC(2);
			I = A[j*WIDTH+i];
			m_a.load(j, i);
			MAGIC(2);
			MAGIC(1);
			B[i*WIDTH+j] = I;	// currently no surport write
			m_b.write(i, j);
			MAGIC(1);
		}
	MAGIC(3);
/////////////// print result
#ifdef PRINT
	printf("\nA:\n");
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			printf("%d ", A[i*WIDTH+j]);
		printf("\n");
	}
	printf("\nB:\n");
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			printf("%d ", B[i*WIDTH+j]);
		printf("\n");
	}
#endif
/////////////// free
	free(A);
	free(B);

	damemory.report("tp.csv");
	return 0;
}
