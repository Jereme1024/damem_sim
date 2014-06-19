# include "magic-instruction.h"
# include <stdio.h> 
# include <stdlib.h> 
# include <time.h>
# include <limits.h>
//# define WIDTH 5 
//# define MAX 10
//# define PRINT
#define PLACEMENT_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/base.in"
#define REGISTER_INFO_FILE "/host/home/vegetablebird/simics-workspace-3.0/regs.in"
//#define PLACEMENT_INFO_FILE "base.in"
//#define REGISTER_INFO_FILE "regs.in"

#include "include/damemory.hpp"

void print(int *s, int i, int j) 
{ 
	if (i == j) 
		printf(" A%d ",i); 
	else 
	{ 
		printf(" ( "); 
		print(s, i, s[i*WIDTH+j]); 
		print(s, s[i*WIDTH+j] + 1, j); 
		printf(" ) "); 
	} 
} 
void printm(int *m, int n) 
{ 
	int i,j; 
	for(i=1;i<=n;i++) 
	{ 
		for(j=1;j<=n;j++) 
		{ 
			printf("%5d",m[i*WIDTH+j]); 
		} 
		printf("\n\n"); 
	} 
	printf("\nThe No. of multiplication required is : %d",m[1*WIDTH+n]); 
} 

void Matrix_Chain_Order(int p[],int num) 
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

	int *m;
	int *s;
	int q = 0; 
	int i, j, k, l; 
	int n = num; 

	//FILE *ofile;
	//printf("multiplex\tmatrix size: (%d, %d)\tvalue range: (1, %d)\n", WIDTH, WIDTH, MAX);
/////////////// malloc
	m = (int *)malloc(WIDTH*WIDTH*sizeof(int));
	auto m_m = damemory.allocate("m", WIDTH, WIDTH, sizeof(int));
	s = (int *)malloc(WIDTH*WIDTH*sizeof(int));
	if (!m || !s)
	{
		printf("malloc failed\n");
		exit(1);
	}
	//printf("base: %p\tsize: (%d, %d)\n", m, WIDTH, WIDTH);
	//printf("base: %p\tsize: (%d, %d)\n", s, WIDTH, WIDTH);
/////////////// declare 2d memory
	//ofile = fopen(PLACEMENT_INFO_FILE, "w");
	//if (!ofile)
	//{
	//	printf("open file failed: %s\n", PLACEMENT_INFO_FILE);
	//	exit(1);
	//}
	//fprintf(ofile, "%p %d %d\n", m, WIDTH, WIDTH);
	//fprintf(ofile, "%p %d %d\n", s, WIDTH, WIDTH);
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
	//fprintf(ofile, "%p\n", &l);
	//fprintf(ofile, "%p\n", &n);
	//fprintf(ofile, "%p\n", &q);
	//fprintf(ofile, "%p\n", &m);
	//fprintf(ofile, "%p\n", &s);
	//fflush(ofile);
	//fclose(ofile);
/////////////// matrix chain order
	for(i = 1; i <= n; i++) 
	{
		m[i*WIDTH+i] = 0; 
		m_m.write(i, i);
	}
	for(l = 2; l <= n; l++) 
		for(i = 1; i <= (n - l + 1); i++) 
		{
			j = i + l - 1; 
			m[i*WIDTH+j] = INT_MAX; 
			m_m.write(i, j);
		}

	MAGIC(3);
	//for(l = 2000; l <= n; l++) 
	for(l = 1; l <= n; l++) 
		for(i = 1; i <= (n - l + 1); i++) 
		{ 
			j = i + l - 1; 
//			m[i*WIDTH+j] = INT_MAX; 
			for(k = i; k <= j - 1; k++) 
			{ 
				MAGIC(1);
				q = m[i*WIDTH+k];
				m_m.load(i, k);
				MAGIC(1);
				MAGIC(2);
			  	q += m[(k+1)*WIDTH+j] + p[i-1] * p[k] * p[j]; 
			  	m_m.load(k+1, j);
				MAGIC(2);
				MAGIC(1);
				if(q < m[i*WIDTH+j]) 
				{ 
					m[i*WIDTH+j] = q; 
					m_m.write(i, j);
#ifdef PRINT
					s[i*WIDTH+j] = k; 
#endif
				} 
				m_m.load(i, j);
				MAGIC(1);
			} 
		} 
	MAGIC(3);
#ifdef PRINT
	printf("MULTIPLICATION SEQUENCE IS : "); 
	printf("\n\n\t"); 
	print(s, i-1, j); 
	printf("\n\n"); 
	printf("The Minimum No. of Multiplication Required is:\n\n"); 
	printm(m,n); 
	printf("\n");
#endif
/////////////// free
	free(m);
	free(s);

	damemory.report("chain.csv");
} 


int main() 
{ 
	int i;
	int num=WIDTH-1;
	int p[WIDTH]={0}; 
	srand(time(0));
	for(i=0;i<=num;i++) 
		p[i] = (rand()%MAX)+1;
#ifdef PRINT
	printf("matrix size sequence: ");
	for(i=0;i<=num;i++) 
		printf("%d ", p[i]);
	printf("\n");
#endif
	Matrix_Chain_Order(p,num); 
	return 0;
}

