#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "calcenergy.h"
#include "findenergy.h"

#define arraySize(x) (sizeof(x)/sizeof((x)[0]))
#define MAX_ZEROCROSS 16

int main(int argc, char *argv[]) {

	// open file	
	FILE *f;
	f = fopen("sample.csv","r");

	if (f == NULL) {
		fprintf(stderr, "Can't open the file.");
		exit(1);
	}

	// count of lines
	int ch = 0;
	unsigned long lines;
	while (!feof(f)) {
		ch = fgetc(f);
		if (ch == '\n')
			lines++;
	}
	fseek(f, 0L, SEEK_SET);
	
	// three vectors
	double *t = (double*)malloc(lines * sizeof(double));
	double *u = (double*)malloc(lines * sizeof(double));
	double *i = (double*)malloc(lines * sizeof(double));
	if (t == NULL || u == NULL || i == NULL) {
		fprintf (stderr, "Memory not allocated");	
		exit(1);	
	}

	// upload vectors
	char 
		c[lines],
		*line = {0};
	int 
		x = 0, 
		y = 0;
	while(fgets(c,lines,f) != NULL) {
		x = 0;
		line = strtok(c, ";");
		while (line != NULL) {
			switch (x) {
				case 0:
					*(t+y) = atof(line); break;
				case 1:
					*(u+y) = atof(line); break;
				case 2:
					*(i+y) = atof(line); break;
				default:
					break;				
			}
			line = strtok(NULL,";");			
			x++;
		}
		y++;
	}
	fclose(f);
		
	// values of sample file (time [s], supply [V], phase_of_motor [i])	
	double val_frequency = calc_frequency(t, u, lines);
	printf ("Freq: %lf\n", val_frequency);
	double *val_peaks = find_peaks(t, u, i, 1/val_frequency, lines);
	double val_phi = calc_phi(val_peaks[1],val_peaks[3],1/val_frequency);
	printf ("phi: %lf\n",val_phi);
	double val_phi_rad = calc_phi_rad(val_phi);
	printf ("phi_rad: %lf\n",val_phi_rad);
	double val_U_rms = calc_U_rms(val_peaks[0]);
	printf ("U_rms: %lf\n",val_U_rms);	
	double val_I_rms = calc_I_rms(val_peaks[2]);
	printf ("I_rms: %lf\n",val_I_rms);	
	double val_S = calc_S(val_U_rms, val_I_rms);
	printf ("S: %lf\n",val_S);	
	double val_P = calc_P(val_S, val_phi_rad);
	printf ("P: %lf\n",val_P);		
	double val_Q = calc_Q(val_S, val_phi_rad);
	printf ("Q: %lf\n",val_Q);	
	double val_PF = calc_PF(val_phi_rad);
	printf ("PF: %lf\n",val_PF);	

}
