#include "magic-instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"
//#define WIDTH 100
//#define PRINT
//#define DEFAULT_DATA

#ifdef DEFAULT_DATA
#define WIDTH 6
#endif
#define n WIDTH-1
int main()
{
	int i, j, l, r;
	float t;
	float p[WIDTH] = {0, 0.15, 0.1, 0.05, 0.1, 0.2};
	float q[WIDTH] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};
	int *root;
	float *e;
	float *w;
	//FILE *ofile;
	//printf("&i: %p\t&j: %p\t&l: %p\t&r: %p\t&t: %p\n", &i, &j, &l, &r, &t);
	//printf("&e: %p\n", &e);
	//printf("transaction\tmatrix size: (%d, %d)\n", WIDTH, WIDTH);
/////////////// malloc
	root = (int *)malloc(WIDTH*WIDTH*sizeof(int));
	e = (float *)malloc((WIDTH+1)*(WIDTH+1)*sizeof(float));
	w = (float *)malloc((WIDTH+1)*(WIDTH+1)*sizeof(float));
	if (!root || !e || !w)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", e, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", e, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &l);
	//fprintf(ofile, "%p\n", &r);
	//fprintf(ofile, "%p\n", &t);
	//fprintf(ofile, "%p\n", &e);
	//fprintf(ofile, "%p\n", &w);
	//fflush(ofile);
	//fclose(ofile);
/////////////// initialization
#ifndef DEFAULT_DATA
	srand(time(0));
	j = 0;
	for (i=0; i<WIDTH; i++)
	{
		p[i] = rand()%1000+1;
		q[i] = rand()%1000+1;
		j += p[i] + q[i];
	}
	j -= p[0];
	p[0] = 0;
	for (i=0; i<WIDTH; i++)
	{
		q[i] /= j;
		p[i] /= j;
	}
#endif
	for (i=0; i<WIDTH; i++)
		for (j=0; j<WIDTH; j++)
		{
			e[i*(WIDTH+1)+j] = w[i*(WIDTH+1)+j] = 0;
			root[i*WIDTH+j] = 0;
		}
/*	for (i=0; i<WIDTH; i++)
		e[(n+1)*(WIDTH+1)+i] = w[(n+1)*(WIDTH+1)+i] = 0;
	free(root);
	free(e);
	free(w);
	return 0;*/
#ifdef PRINT
	for (l=1; l<=n; l++)
		for (i=1; i<=n-l+1; i++)
		{
			j = i + l - 1;
			e[i*(WIDTH+1)+j] = FLT_MAX;
			w[i*(WIDTH+1)+j] = w[i*(WIDTH+1)+(j-1)] + p[j] + q[j];
		}
	for (i=1; i<=n+1; i++)
	{
		e[i*(WIDTH+1)+(i-1)] = q[i-1];
		w[i*(WIDTH+1)+(i-1)] = q[i-1];
	}
#endif
/////////////// optimal binary search tree
	MAGIC(3);
	for (l=2000; l<=n; l++)
		for (i=1; i<=n-l+1; i++)
		{
			j = i + l - 1;
			w[i*WIDTH+j] = w[i*WIDTH+(j-1)] + p[j] + q[j];
			for (r=i; r<=j; r++)
			{
				MAGIC(2);
				t = e[(r+1)*WIDTH+j];
				MAGIC(2);
				MAGIC(1);
				t += e[i*WIDTH+(r-1)] + w[i*WIDTH+j];
				if (t < e[i*WIDTH+j])
				{
					e[i*WIDTH+j] = t;
#ifdef PRINT
					root[i*WIDTH+j] = r;
#endif
				}
				MAGIC(1);
			}
		}
	MAGIC(3);
/////////////// print result
#ifdef PRINT
	printf("p: \n");
	for (i=0; i<WIDTH; i++)
		printf("%f ", p[i]);
	printf("\n");
	printf("q: \n");
	for (i=0; i<WIDTH; i++)
		printf("%f ", q[i]);
	printf("\n");
	printf("root:\n");
	for (i=1; i<WIDTH; i++)
	{
		for (j=1; j<WIDTH; j++)
			printf("%d ", root[i*WIDTH+j]);
		printf("\n");
	}
	printf("e:\n");
	for (i=1; i<=WIDTH; i++)
	{
		for (j=0; j<WIDTH; j++)
			printf("%f ", e[i*(WIDTH+1)+j]);
		printf("\n");
	}
	printf("w:\n");
	for (i=1; i<=WIDTH; i++)
	{
		for (j=0; j<WIDTH; j++)
			printf("%f ", w[i*(WIDTH+1)+j]);
		printf("\n");
	}
#endif
/////////////// free
	free(root);
	free(e);
	free(w);
	return 0;
}
