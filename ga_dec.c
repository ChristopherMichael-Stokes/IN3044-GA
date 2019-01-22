//using decimal representation for chroms
#include "ga.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct pop* init_population(size_t popsize, size_t chromlength, 
		int seed, double max, double min, int dp) {
	if (popsize < 1 || chromlength< 2 || chromlength% 2 != 0) {
		perror("invalid population or chromosone size");
		return NULL;
	} else if (seed < 0) {
		seed = time(NULL);
	}
	srand(seed);
	struct pop* p = malloc(sizeof(struct pop) + sizeof(struct chrom)*popsize);
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
		c->genes = malloc(sizeof(struct gene)*chromlength);
		c->chromlength = &p->chromlength;
		if (NULL == c->genes) {
			perror("cannot allocate space for genes");
			exit(-1);
		}
		for (int j = 0; j < chromlength; ++j) {
			c->genes[j].x1 = 
				min + (float)rand()/(float)RAND_MAX * (max - min);
			c->genes[j].x2 = 
				min + (float)rand()/(float)RAND_MAX * (max - min);
			c->genes[j].alive = true;
		}
	}
	return p;
}

static double evaluate(struct gene *g, double (*eval)(double[])) {
	double xs[] = {g->x1, g->x2};
	return 0.0 - eval(xs);
}

void printpop(struct pop* p,  double (*eval)(double[])) {
	printf("population size: %zu, chromosone length: %zu,"
			" min/max: %lf, %lf, decimal places: %zu\n",
			p->size, p->chromlength, p->min, p->max, p->dp);
	for (int i = 0; i < p->size; ++i) {
		printf("chromosone %d:\n",i);
		for (int j = 0; j < p->chromlength; ++j) {
			//printf("x1: %f, x2: %f\n",p->chroms[i].genes[j].x1,
			//	p->chroms[i].genes[j].x2);
			printf("x1: %f, x2: %f, alive %d\tfitness %f\n",p->chroms[i].genes[j].x1,
				p->chroms[i].genes[j].x2,p->chroms[i].genes[j].alive,
				evaluate(&p->chroms[i].genes[j],eval));
		}
	}	
	putchar('\n');
}

void freepop(struct pop* p) {
	//free each inner alloc for the population 
	//then free the alloc for the population
	for (int i = 0; i < p->size; ++i) {
		struct chrom c = p->chroms[i];
		//free(c.genes);
	}
	free(p);
}

static float prob() {
	return (float)rand() / (float)RAND_MAX;
}

void selection(struct chrom* c, double fitness[]) {
	//chance for weaker gene to win
	const float win_chance = 0.05;
	size_t len = *c->chromlength;
	//fight pairs of genes
	for (int i = 0; i < len; i += 2) {
		int loser = fitness[i] < fitness[i+1] ? i : i+1;
		if (prob() <= win_chance) {
			loser = loser == i ? i+1 : i;
		}
		c->genes[loser].alive = false;
	}
}

void crossover(struct pop * p, struct chrom* c, double fitness[]) {
	float mutation_rate = 0.1;
	size_t len = *c->chromlength, cross_len = len/2;

	struct gene children[cross_len], parents[cross_len];
	int current_parent = 0, current_gene = 0;
	for (int i = 0; i < len; ++i) {
		if (c->genes[i].alive) {
			parents[current_parent++] = c->genes[i];
		}
	}

	for (int i = 0; i < cross_len; ++i) {
		struct gene a = parents[i], b = parents[(i+1)%cross_len];
		size_t width = 20;
		char a_x1[width], a_x2[width], b_x1[width], b_x2[width], c_x1[width], c_x2[width];
		sprintf(a_x1, "%020.6f", a.x1);
		sprintf(a_x2, "%020.6f", a.x2);
		sprintf(b_x1, "%020.6f", b.x1);
		sprintf(b_x2, "%020.6f", b.x2);
		sprintf(c_x1, "%020.6f", 0);
		sprintf(c_x2, "%020.6f", 0);
		for (int j = 0; j<strlen(a_x1); ++j) {
			if (prob() > 0.5)
				c_x1[j] = a_x1[j];
			else
				c_x1[j] = b_x1[j];
			if (prob() <= mutation_rate && c_x1[j] != '.' && j >= width - 9){
			//	printf("mutation from: %s, %c to ",c_x1,c_x1[j]);
				c_x1[j] = '0'+(int)(((float) rand() / (float) RAND_MAX) * 10);
			//	printf("%c, string:%s\n",c_x1[j],c_x1);
			}
		}
		for (int j = 0; j<strlen(a_x2); ++j) {
			if (prob() > 0.5)
				c_x2[j] = a_x2[j];
			else
				c_x2[j] = b_x2[j];
			if (prob() <= mutation_rate && c_x2[j] != '.' &&j >= width - 9) {
				c_x2[j] = '0'+(int)(((float) rand() / (float) RAND_MAX) * 10);
			}
		}
		c_x1[width-1] = '\0'; c_x2[width-1] = '\0';
		children[current_gene].x1 = atof(c_x1);
		children[current_gene].x2 = atof(c_x2);
		++current_gene;
	}




	current_gene = 0;
	for (int i = 0; i < len; ++i) {
		if (!c->genes[i].alive) {
			c->genes[i].x1 = children[current_gene].x1;
			c->genes[i].x2 = children[current_gene].x2;
			c->genes[i].alive = true;
			++current_gene;
		}

	}
}


void fitness(struct chrom* c, double fitness[], double (*eval)(double[])) {
	for (int i = 0; i < *c->chromlength; ++i)
		fitness[i] = evaluate(&c->genes[i], eval);
}


void print_fittest(struct pop *p, double (*eval)(double[])) {
	int i, j, best_i = 0, best_j = 0;
	struct gene best_gene = p->chroms[0].genes[0];
	double best_fitness = evaluate(&best_gene, eval);
	putchar('\n');
	for (i = 0; i < p->size; ++i) {
		struct chrom c = p->chroms[i];
		for (j = 0; j < *c.chromlength; ++j) {
			struct gene g = c.genes[j];
			double fitness = evaluate(&g, eval);
			if (fitness > best_fitness) {
				best_i = i; best_j = j;
				best_gene = g;
				best_fitness = fitness;
			}
		}
	}
	printf("best gene is gene %d, from chromosone %d\n"
			"with x1: %f\tx2: %f\tand fitness: %lf\n",
			best_j, best_i, best_gene.x1, best_gene.x2, best_fitness);



}
