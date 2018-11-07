#ifndef __GA__
#define __GA__

extern float mutation;
struct gene;
struct pop;

//modifies a and b in place
void crossover(struct gene* a, struct gene* b, float mutation);
struct pop* init_population(int size, int seed, double max, double min);
void printpop(struct pop* population);
void freepop(struct pop* population);
double fitness(struct gene* g, double (*eval)(double[]));

#endif
