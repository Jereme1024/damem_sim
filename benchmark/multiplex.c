#include "magic-instruction.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define MAX 5
//#define WIDTH 3
//#define PRINT
int main()
{
	int i, j, k;
	int m, n;
	register int I, J;
	int *A, *B, *C;
	//FILE *ofile;
	m = n = WIDTH;
	//printf("multiplex\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", m, n, MAX);
/////////////// malloc
	A = (int *)malloc(m*n*sizeof(int));
	B = (int *)malloc(m*n*sizeof(int));
	C = (int *)malloc(m*n*sizeof(int));
	if (!A || !B || !C)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", A, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", B, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", C, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", A, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", B, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", C, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &A);
	//fprintf(ofile, "%p\n", &B);
	//fprintf(ofile, "%p\n", &C);
	//fflush(ofile);
	//fclose(ofile);
/////////////// initialization
	srand(time(0));
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
		{
			I = rand()%(MAX+1);
			A[i*WIDTH+j] = I;	// currently no surport write
			I = rand()%(MAX+1);
			B[i*WIDTH+j] = I;	// currently no surport write
			C[i*WIDTH+j] = 0;	// currently no surport write
		}
/////////////// multiplex
	MAGIC(3);
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
		{
			I = 0;
			for (k=0; k<WIDTH; k++)
			{
				MAGIC(1);
				J = A[i*WIDTH+k];
				MAGIC(1);
				MAGIC(2);
				I += J * B[k*WIDTH+j];
				MAGIC(2);
			}
			MAGIC(1);
			C[i*WIDTH+j] = I;	// currently no surport write
			MAGIC(1);
		}
	MAGIC(3);
#ifdef PRINT
/////////////// print results
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
	printf("\nC:\n");
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
			printf("%d ", C[i*WIDTH+j]);
		printf("\n");
	}
#endif
/////////////// free
	free(A);
	free(B);
	free(C);
	return 0;
}
