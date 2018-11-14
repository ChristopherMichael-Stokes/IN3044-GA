#include "foxhole.h"
#include "ga.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	double result;
	if (argc > 2) {
		double x[] = {atof(argv[1]),atof(argv[2])};
		result = foxholes(x);
	} else {
		double x[] = {20, 13};
		result = foxholes(x);
	}
	struct pop* p = init_population(10,10,-1,40,-40,3);
	printpop(p);
	putchar('\n');
	freepop(p);
	printf("%lf\n", result);
	return 0;
}
