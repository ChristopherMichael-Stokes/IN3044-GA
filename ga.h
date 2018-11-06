#ifndef __GA__
#define __GA__

struct gene;
struct pop;
//modifies a and b in place
void crossover(struct gene* a, struct gene* b);
struct pop* init_population(int size);
double fitness(struct gene* g);

#endif
