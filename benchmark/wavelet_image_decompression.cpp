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

#include "include/damemory.hpp"

int WIDTH, sqrtWIDTH;

int main(int argc, char *argv[])
{
	// DA memory create
	const int h_mem = atoi(argv[1]);
	const int w_mem = atoi(argv[2]);
	const int h_page = atoi(argv[3]);
	const int w_page = atoi(argv[4]);
	const int h_dataset = atoi(argv[5]);
	const int w_dataset = atoi(argv[6]);

	WIDTH = atoi(argv[7]);
	sqrtWIDTH = sqrt(WIDTH);

	// POLICY = (Arranger_padding | Arranger_concatenating | Arranger_hyperpadding)
	DAmemory<POLICY, Scheduler_LRU> damemory(h_mem, w_mem, h_page, w_page, h_dataset, w_dataset);

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
	auto m_c = damemory.allocate("c", WIDTH+1, WIDTH+1, sizeof(float));
	cp = (float *)malloc((WIDTH+1)*(WIDTH+1)*sizeof(float));
	auto m_cp = damemory.allocate("cp", WIDTH+1, WIDTH+1, sizeof(float));
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
/////////////// standard wavelet decompression of image (Haar basis)
	MAGIC(3);
	MAGIC(2);
	for (column=1; column<=WIDTH; column++)
	{
		for (j=2; j<=WIDTH; j*=2)
			for (k=1; k<=j/2; k++)
			{
				cp[(2*k-1)*WIDTH+column] = (c[k*WIDTH+column] + c[(j/2+k)*WIDTH+column]) / sqrt2;
				m_c.load(k * WIDTH /  (WIDTH + 1), column);
				m_c.load((j / 2 + k) * WIDTH /  (WIDTH + 1), column);
				m_cp.write((2 * k - 1) * WIDTH /  (WIDTH + 1), column);
				cp[(2*k)*WIDTH+column] = (c[k*WIDTH+column] - c[(j/2+k)*WIDTH+column]) / sqrt2;
				m_c.load(k * WIDTH /  (WIDTH + 1), column);
				m_c.load((j / 2 + k) * WIDTH /  (WIDTH + 1), column);
				m_cp.write((2 * k) * WIDTH /  (WIDTH + 1), column);
			}
//		for (i=1; i<=WIDTH; i++)
//			c[i*WIDTH+column] = c[i*WIDTH+column] / sqrt(WIDTH);
	}
	MAGIC(2);
	MAGIC(3);
	MAGIC(1);
	for (row=1; row<=WIDTH; row++)
	{
		for (j=2; j<=WIDTH; j*=2)
			for (k=1; k<=j/2; k++)
			{
				cp[(2*k-1)+WIDTH*row] = (c[k+WIDTH*row] + c[(j/2+k)+WIDTH*row]) / sqrt2;
				m_c.load(k * WIDTH /  (WIDTH + 1), row);
				m_c.load((j / 2 + k) * WIDTH /  (WIDTH + 1), row);
				m_cp.write((2 * k - 1) * WIDTH /  (WIDTH + 1), row);
				cp[(2*k)+WIDTH*row] = (c[k+WIDTH*row] - c[(j/2+k)+WIDTH*row]) / sqrt2;
				m_c.load(k * WIDTH /  (WIDTH + 1), row);
				m_c.load((j / 2 + k) * WIDTH /  (WIDTH + 1), row);
				m_cp.write((2 * k) * WIDTH /  (WIDTH + 1), row);
			}
//		for (i=1; i<=WIDTH; i++)
//			c[row*WIDTH+i] = c[row*WIDTH+i] / sqrt(WIDTH);
	}
	MAGIC(1);
	MAGIC(3);
/////////////// denormalization
	for (row=1; row<=WIDTH; row++)
		for (i=1; i<=WIDTH; i++)
			c[row*WIDTH+i] = c[row*WIDTH+i] / sqrtWIDTH;
	for (column=1; column<=WIDTH; column++)
		for (i=1; i<=WIDTH; i++)
			c[i*WIDTH+column] = c[i*WIDTH+column] / sqrtWIDTH;
/////////////// free
	free(c);
	free(cp);

	damemory.report("wde.csv");

	return 0;
}
