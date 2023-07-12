#ifndef CALCENERGY_FILE
#define CALCENERGY_FILE

double calc_frequency(double *t, double *u, int lines);
double calc_phi(double time_of_u_peak, double time_of_i_peak, double periodic);
double calc_phi_rad(double phi);
double calc_U_rms(double U_peak);
double calc_I_rms(double I_peak);
double calc_S(double U_rms, double I_rms);
double calc_P(double S, double phi_rad);
double calc_Q(double S, double phi_rad);
double calc_PF(double phi_rad);

#endif
