#include "rk4.hpp"

void rk4_API (int id, double t0, double u[], double tmax, double dt);
void rk4_API (int id, double t0, double x0, double v0, double tmax, double dt,
	      double & x1, double & v1);
double *rk4_f ( double t, int n, double u[] );
