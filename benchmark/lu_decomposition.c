#include "magic-instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define WIDTH 5
//#define MAX 10
//#define PRINT

void mprint(float *aa)
{
	int i,j;
	for(i=1; i<WIDTH; i++){
		for(j=1; j<WIDTH; j++)
			printf("%10.5e ",aa[i*WIDTH+j]);
		printf("\n");
	}
}

int main()
{
	int i,j,k;
	float I;
	float *a, *L, *U;
	//FILE *ofile;
	//printf("&i: %p\t&j: %p\t&k: %p\t&I: %p\n", &i, &j, &k, &I);
	//printf("&a: %p\t&L: %p\t&U: %p\n", &a, &L, &U);
	//printf("transaction\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", WIDTH, WIDTH, MAX);
/////////////// malloc
	a = (float *)malloc(WIDTH*WIDTH*sizeof(float));
	L = (float *)malloc(WIDTH*WIDTH*sizeof(float));
	U = (float *)malloc(WIDTH*WIDTH*sizeof(float));
	if (!a || !L || !U)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", a, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", L, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", U, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", a, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", L, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", U, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &a);
	//fprintf(ofile, "%p\n", &L);
	//fprintf(ofile, "%p\n", &U);
	//fflush(ofile);
	//fclose(ofile);
/////////////// initialization
	srand(time(0));
	for(i=1; i<WIDTH; i++)
		for(j=1;j<WIDTH;j++)
			a[i*WIDTH+j] = (int)(rand()%(MAX+1));
/* start to the procedure of LU decomposition */
	for(i=0; i<WIDTH; i++)
		for(j=0; j<WIDTH;j++)
		{
			L[i*WIDTH+j]=0.0;
			U[i*WIDTH+j]=0.0;
		}
	for(i=1; i<WIDTH; i++)
		L[i*WIDTH+1]=a[i*WIDTH+1];
	for(j=1; j<WIDTH; j++)
		U[1*WIDTH+j]=a[1*WIDTH+j]/L[1*WIDTH+1];
	for(j=2; j<WIDTH; j++)
		U[j*WIDTH+j]=1.0;
/////////////// LU-decomposition kernel
	MAGIC(3);
//	for(j=2; j<WIDTH; j++){
	for(j=WIDTH/2; j<WIDTH; j++){
		for(i=j; i<WIDTH;i++){
			MAGIC(2);
			L[i*WIDTH+j] = a[i*WIDTH+j];
			MAGIC(2);
			for(k=1;k<=j-1;k++)
			{
				MAGIC(1);
				I = L[i*WIDTH+k];
				MAGIC(1);
				MAGIC(2);
				L[i*WIDTH+j] -= I * U[k*WIDTH+j];
				MAGIC(2);
			}
		}
//		MAGIC(1);
//		U[j*WIDTH+j]=1.0;
//		MAGIC(1);
		for(i=j+1;i<WIDTH;i++){
			MAGIC(1);
			U[j*WIDTH+i] = a[j*WIDTH+i];
			MAGIC(1);
			for(k=1; k<=j-1;k++)
			{
				MAGIC(2);
				I = U[k*WIDTH+i];
				MAGIC(2);
				MAGIC(1);
				U[j*WIDTH+i] -= L[j*WIDTH+k] * I;
				MAGIC(1);
			}
			MAGIC(1);
			U[j*WIDTH+i] /= L[j*WIDTH+j];
			MAGIC(1);
		}
	}
	MAGIC(3);
/////////////// print result
#ifdef PRINT
	printf("a\n");
	mprint(a);
	printf("L\n");
	mprint(L);
	printf("U\n");
	mprint(U);
#endif
/////////////// free
	free(a);
	free(L);
	free(U);
	return 0;
}/*End of main() */
 
