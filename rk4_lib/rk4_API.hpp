#include "rk4.hpp"

void rk4_API (int id, double t0, double u[], double tmax, double dt);
double *rk4_f ( double t, int n, double u[] );
