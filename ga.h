#ifndef __GA__
#define __GA__
#include <stdlib.h>
#include <stdbool.h>

extern float mutation;

struct gene {
	float x1, x2;
	bool alive;
};

struct chrom {
	struct gene *genes;
	size_t *chromlength;
};

struct pop {
	double min, max;
	size_t size, chromlength, dp;
	struct chrom chroms[0];
};

//modifies a and b in place
void crossover(struct pop * p, struct chrom* c, double fitness[]);
struct pop* init_population(size_t popsize, size_t chromlength, int seed, double max, double min, int dp);
void printpop(struct pop* p, double (*eval)(double[]));
void freepop(struct pop* p);
void fitness(struct chrom* c, double fitness[], double (*eval)(double[]));
void selection(struct chrom* c, double fitness[]);
void print_fittest(struct pop *p, double  (*eval)(double[]));

#endif
