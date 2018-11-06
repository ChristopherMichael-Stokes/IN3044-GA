#include "foxhole.h"
#include "ga.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double Xi = -31.97833, min = -40, max = 40;
static const int ai0[5] = {-32, -16, 0, 16, 32};

double foxhole(double x[2]) {
	int a[2][25];
	for (int i = 0; i < 25; ++i) {
		//repmat(ai0, 1, 5);
		a[0][i] = ai0[i%5]; 
		//reshape(repmat(ai0, 5 , 1), 1, 25);
		for (int j = 0; j < 5; ++j) 
			if ((j*5)-i < 1) a[1][i] = ai0[j];
	}

	double tmp = 0, tmp2;
	for (int i = 0; i < 25; ++i) {
		tmp2= 0;
		for (int j = 0; j < 2; ++j) 
			tmp2 += pow((x[j] - a[j][i]), 6);

		tmp = tmp + 1 / (i + tmp2);
	}
	return 1 / (0.002 + tmp);
}
int main(int argc, char** argv) {
	double result;
	if (argc > 2) {
		double x[] = {atof(argv[1]),atof(argv[2])};
		result = foxhole(x);
	} else {
		double x[] = {20, 13};
		result = foxhole(x);
	}

	printf("%lf\n", result);
	return 0;
}
