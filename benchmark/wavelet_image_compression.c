#include "magic-instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define WIDTH 128
//#define MAX 5
//#define PRINT
#define sqrt2 1.41421356
//#define sqrtWIDTH sqrt(WIDTH)
int main()
{
//	float c[WIDTH+1*WIDTH+WIDTH+1];	// c[2^7*WIDTH+2^8]
//	float cp[WIDTH+1*WIDTH+WIDTH+1];	// c[2^7*WIDTH+2^8]
	float *c, *cp;
	int row, column;
	int i,j,k;
	//FILE *ofile;
	//printf("&i: %p\t&j: %p\t&k: %p\t&row: %p\t&column: %p\n", &i, &j, &k, &row, &column);
	//printf("&a: %p\t&b: %p\n", &c, &cp);
//	printf("transaction\tmatrix size: (%d, %d)\tvalue range: (0, %d)\n", WIDTH, WIDTH, MAX);
	//printf("transaction\tmatrix size: (%d, %d)\n", WIDTH, WIDTH);
/////////////// malloc
	c = (float *)malloc((WIDTH+1)*(WIDTH+1)*sizeof(float));
	cp = (float *)malloc((WIDTH+1)*(WIDTH+1)*sizeof(float));
	if (!c || !cp)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", c, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", cp, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", c, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", cp, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &row);
	//fprintf(ofile, "%p\n", &column);
	//fflush(ofile);
	//fclose(ofile);
/////////////// initialization
	for (row=1; row<=WIDTH; row++)
		for (i=1; i<=WIDTH; i++)
			c[row*WIDTH+i] = c[row*WIDTH+i] / sqrtWIDTH;
	for (column=1; column<=WIDTH; column++)
		for (i=1; i<=WIDTH; i++)
			c[i*WIDTH+column] = c[i*WIDTH+column] / sqrtWIDTH;
/////////////// standard wavelet compression of image (Haar basis)
	MAGIC(3);
	MAGIC(1);
	for (row=1; row<=WIDTH; row++)
	{
//		for (i=1; i<=WIDTH; i++)
//			c[row*WIDTH+i] = c[row*WIDTH+i] / sqrt(WIDTH);
		for (j=WIDTH; j>=2; j/=2)
			for (k=1; k<=j/2; k++)
			{
				cp[row*WIDTH+k] = (c[row*WIDTH+(2*k-1)]+c[row*WIDTH+(2*k)]) / sqrt2;
				cp[row*WIDTH+(j/2+k)] = (c[row*WIDTH+(2*k-1)] - c[row*WIDTH+(2*k)]) / sqrt2;
			}
	}
	MAGIC(1);
	MAGIC(3);
	MAGIC(2);
	for (column=1; column<=WIDTH; column++)
	{
//		for (i=1; i<=WIDTH; i++)
//			c[i*WIDTH+column] = c[i*WIDTH+column] / sqrt(WIDTH);
		for (j=WIDTH; j>=2; j/=2)
			for (k=1; k<=j/2; k++)
			{
				cp[k*WIDTH+column] = (c[(2*k-1)*WIDTH+column]+c[(2*k)*WIDTH+column]) / sqrt2;
				cp[(j/2+k)*WIDTH+column] = (c[(2*k-1)*WIDTH+column] - c[(2*k)*WIDTH+column]) / sqrt2;
			}
	}
	MAGIC(2);
	MAGIC(3);
/////////////// free
	free(c);
	free(cp);
	return 0;
}
