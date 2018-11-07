//using decimal representation for genes
#include "ga.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct gene {
	float chrom_a, chrom_b;
};

struct pop {
	struct gene* genes;
	size_t size;
};

struct pop* init_population(int size, int seed, double max, double min) {
	if (size < 2) {
		perror("population size too small");
		return NULL;
	} else if (seed < 0) {
		seed = time(NULL);
	}
	srand(seed);
	struct pop* p = malloc(sizeof(struct pop)+sizeof(struct gene)*size);
	for (int i = 0; i < size; ++i) {
		p->genes[i].chrom_a = min + 
			(float)rand()/RAND_MAX * (max - min);
		p->genes[i].chrom_b = min +
			(float)rand()/RAND_MAX * (max - min);
	}
	return p;
}

void printpop(struct pop* population) {
	
}

void freepop(struct pop* population) {
	free(population);
}
