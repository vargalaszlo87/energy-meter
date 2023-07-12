#include <stdlib.h>
#include <math.h>

#include "findenergy.h"

double *find_peaks(double *t, double *u, double *i, double period, int lines) {
	int 
		x = 1; 
	double 
		p[2][2] = {{0,0},{0,0}},
		item[2] = {*(u+x),*(i+x)};
	// two peaks at the same time!
	item[1] = *(i+x);

	while (++x < lines) {
		if (*(u+x) - item[0] > 0 && p[0][1] < 1)
			item[0] = *(u+x), p[0][0] = *(t+x);
		else
			p[0][1] = 1;
		if (*(i+x) - item[1] > 0 && p[1][1] < 1) 
			item[1] = *(i+x), p[1][0] = *(t+x);		
		else
			p[1][1] = 1;
		if (p[0][1] + p[1][1] > 1)
			break;
	}
	// U_peak, time of U_peak, I_peak, time of I_peak
	double *out = (double*)malloc(4 * sizeof(double));
	*(out + 0) = item[0];
	*(out + 1) = p[0][0];
	*(out + 2) = item[1];
	*(out + 3) = p[1][0];

	return out;
}
