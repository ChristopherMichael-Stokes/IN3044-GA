#ifndef __GA__
#define __GA__
#include <stdlib.h>

extern float mutation;

struct gene {
	float x1, x2;
};

struct chrom {
	struct gene *genes;
};

struct pop {
	double min, max;
	size_t size, chromlength, dp;
	struct chrom chroms[0];
};

//modifies a and b in place
void crossover(struct chrom* c, float rate);

struct pop* init_population(size_t popsize, size_t chromlength, int seed, double max, double min, int dp);
void printpop(struct pop* p);
void freepop(struct pop* p);
double fitness(struct chrom* c, double fitness[], double (*eval)(double[]));

#endif
