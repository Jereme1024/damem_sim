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

int main()
{
	int i, j, k;
	float I;
	float *A;
	//FILE *ofile;
	//printf("&i: %p\t&j: %p\t&k: %p\t&I: %p\n", &i, &j, &k, &I);
	//printf("&a: %p\n", &A);
	//printf("transaction\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", WIDTH, WIDTH, MAX);
/////////////// malloc
	A = (float *)malloc(WIDTH*WIDTH*sizeof(float));
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
			A[i*WIDTH+j] = i<j ? i+1 : j+1;
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
/////////////// left-looking cholesky factorization
	MAGIC(3);
	for (j=0; j<WIDTH; j++)
	{
		for (i=j; i<WIDTH; i++)
			for (k=0; k<j; k++)
			{
				MAGIC(1);
				I = A[i*WIDTH+k] * A[j*WIDTH+k];
				MAGIC(1);
				MAGIC(2);
				A[i*WIDTH+j] -= I;
				MAGIC(2);
//				A[i*WIDTH+j] = A[i*WIDTH+j] - A[i*WIDTH+k] * A[j*WIDTH+k];
			}
		MAGIC(1);
//		A[j*WIDTH+j] = A[j*WIDTH+j] * A[j*WIDTH+j];
		I = A[j*WIDTH+j];
		A[j*WIDTH+j] = I * I;
		MAGIC(1);
		MAGIC(2);
		for (i=j+1; i<WIDTH; i++)
			A[i*WIDTH+j] = A[i*WIDTH+j] / A[j*WIDTH+j];
		MAGIC(2);
	}
	MAGIC(3);
/////////////// print result
#ifdef PRINT
	printf("result: \n");
	for (j=0; j<WIDTH; j++)
		for (i=j+1; i<WIDTH; i++)
			A[j*WIDTH+i] = 0;
	for (i=0; i<WIDTH; i++)
	{
		for (j=0; j<WIDTH; j++)
			printf("%f ", A[i*WIDTH+j]);
		printf("\n");
	}
#endif
/////////////// free
	free(A);
	return 0;
}

