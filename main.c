#include "foxhole.h"
#include "ga.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int pop_size, chrom_length, seed, generation, step;
	if (argc > 1  && atoi(argv[1]) == 0) {
		pop_size = 5;
		chrom_length = 4;
		seed = 0;
		step = 5;
	} else if (argc > 4) {
		pop_size = atoi(argv[1]);
		chrom_length = atoi(argv[2]);
		seed = atoi(argv[3]);
		step = atoi(argv[4]);
	} else {
		printf("initial population size: ");
		scanf("%d", &pop_size);
		printf("chromosone length: ");
		scanf("%d", &chrom_length);
		printf("random seed (0 for default): ");
		scanf("%d", &seed);
		printf("amount of generations to run for: ");
		scanf("%d", &step);
		putchar('\n');
	}

	//initialize population
	struct pop* p = init_population(pop_size,chrom_length,seed,max,min,3);
	printf("\tINITIAL POPULATION\n");
	printpop(p,&foxholes);

	generation = 0;
	char repeat;
	do { 
		int begin = generation;
		//generation loop
		while (++generation <= begin + step) {
			for (int i = 0; i < p->size; ++i) {
				//get fitness
				struct chrom * chromosone = &p->chroms[i];
				double f[p->chromlength];
				fitness(chromosone, f, &foxholes);
				selection(chromosone, f);
				printf("chrom %d\n",i);
				crossover(p,chromosone, f);
			}

		}
		printf("current generation: %d\ncurrent population:\n", generation);
		printpop(p, &foxholes);
		print_fittest(p, &foxholes);

		//ask to run again
		printf("continue (y/n): ");
		scanf("%c", &repeat);
		putchar('\n');
	} while (repeat != 'n');






	//free memory
	freepop(p);
	return 0;
}
