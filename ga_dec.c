//using decimal representation for chroms
#include "ga.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct pop* init_population(size_t popsize, size_t chromlength, 
		int seed, double max, double min, int dp) {
	if (popsize < 1 || chromlength< 2 || chromlength% 2 != 0) {
		perror("invalid population or chromosone size");
		return NULL;
	} else if (seed < 0) {
		seed = time(NULL);
	}
	srand(seed);
	struct pop* p =	malloc(sizeof(struct pop)+
			sizeof(struct chrom*)*popsize);
	if (NULL == p) {
		perror("cannot allocate space for population");
		exit(-1);
	}
	p->size = popsize;
	p->chromlength = chromlength;
	p->min = min; p->max = max;
	p->dp = dp;
	for (int i = 0; i < popsize; ++i) {
		struct chrom *c = &p->chroms[i];
		c->genes = malloc(sizeof(struct gene *)*chromlength);
		if (NULL == c->genes);
		printf("%d\n",i);
		for (int j = 0; j < chromlength; ++j) {
			c->genes[j].x1 = 
				min + (float)rand()/RAND_MAX * (max - min);
			c->genes[j].x2 = 
				min + (float)rand()/RAND_MAX * (max - min);
			printf("x1/x2: %f, %f\n",c->genes[j].x1,c->genes[j].x2);
		}
	}
	return p;
}

void printpop(struct pop* p) {
	printf("population size: %zu, chromosone length: %zu,"
			" min/max: %lf, %lf, decimal places: %zu\n",
			p->size, p->chromlength, p->min, p->max, p->dp);
	for (int i = 0; i < p->size; ++i) {
		printf("chromosone %d:\n",i);
		for (int j = 0; j < p->chromlength; ++j) {
			printf("x1: %f, x2: %f\n",p->chroms[i].genes[j].x1,
				p->chroms[i].genes[j].x2);
		}
	}	
}

void freepop(struct pop* p) {
	for (int i = 0; i < p->size; ++i) 
		free(p->chroms[i].genes);
	free(p);
}
