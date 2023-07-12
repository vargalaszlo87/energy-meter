#include <math.h>

#include "calcenergy.h"

#define MAX_ZEROCROSS 16
#define arraySize(x) (sizeof(x)/sizeof((x)[0]))

double calc_frequency(double *t, double *u, int lines) {
	// zero-cross points
	int 
		x = -1,
		y = 0;
	double zeroCross[MAX_ZEROCROSS] = {0};	
	while (++x < lines) {
		if ((*(u+x) == 0 && *(u+(x+1)) > 0) ||
		(*(u+x) <= 0 && *(u+(x+1)) > 0) ||
		(*(u+x) >= 0 && *(u+(x+1)) < 0)) {
			if (y > MAX_ZEROCROSS)
				break;
			zeroCross[y++] = (abs(*(u+x)) < abs(*(u+(x+1)))) ? x : x+1;
		}
	}		
	// frequency
	x = -1;
	double temp = 0;
	while (++x < arraySize(zeroCross)){
		if (*(zeroCross+(x+2)) < 1)
			break;	
		temp += fabs(t[(int)*(zeroCross+x)]-t[(int)*(zeroCross+(x+1))])*2;	
	}
	return 1/((double)temp/x); // Hz	
}

double calc_phi(double time_of_u_peak, double time_of_i_peak, double periodic) {
	return (fabs(time_of_u_peak-time_of_i_peak)/periodic)*180;
}

double calc_phi_rad(double phi) {
	return (phi * M_PI)/180;
}

double calc_U_rms(double U_peak) {
	return U_peak/sqrt(2);
}

double calc_I_rms(double I_peak) {
	return I_peak/sqrt(2);
}

double calc_S(double U_rms, double I_rms) {
	return U_rms * I_rms;
}

double calc_P(double S, double phi_rad) {
	return S*cos(phi_rad);
}

double calc_Q(double S, double phi_rad) {
	return S*sin(phi_rad);
}

double calc_PF(double phi_rad) {
	return cos(phi_rad);
}
