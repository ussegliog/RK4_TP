# include <cmath>
# include <cstdlib>
# include <iomanip>
# include <iostream>

using namespace std;

# include "rk4_API.hpp"

  
//****************************************************************************80

void rk4_API (int id, double t0, double u0[], double tmax, double dt)

//****************************************************************************80
//
//  Purpose:
//
//    RK4_API launchs the RK4 routine for a vector ODE.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
{
  double t1;
  double *u1;
  int i;
  int n = 2;

  cout << "\n";
  cout << "RK4VEC_TEST\n";
  cout << "  RK4VEC takes a Runge Kutta step for a vector ODE.\n";

  cout << "\n";
  cout << "       T       U[0]       U[1]\n";
  cout << "\n";
  

  for ( ; ; )
  {

//
//  Stop if we've exceeded TMAX.
//
    if ( tmax <= t0 )
    {
      break;
    }
//
//  Otherwise, advance to time T1, and have RK4 estimate 
//  the solution U1 there.
//
    t1 = t0 + dt;
    u1 = rk4vec ( t0, n, u0, dt, rk4_f );
//
//  Shift the data to prepare for another step.
//
    t0 = t1;
    for ( i = 0; i < n; i++ )
    {
      u0[i] = u1[i];
    }
    delete [] u1;
  }

  //
  //  Print (T0,U0). // At the last iteration
  //
    cout << "  " << setw(14) << t0
         << "  " << setw(14) << u0[0]
         << "  " << setw(14) << u0[1] << "\n";

  return;
}

//****************************************************************************80

void rk4_API (int id, double t0, double x0, double v0, double tmax, double dt,
	      double & x1, double & v1)

//****************************************************************************80
//
//  Purpose:
//
//    RK4_API launchs the RK4 routine for a vector ODE.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
{
  double t1;
  double * u0 = new double[2];
  u0[0] = x0;
  u0[1] = v0;
  double *u1;
  int i;
  int n = 2;

  for ( ; ; )
  {

//
//  Stop if we've exceeded TMAX.
//
    if ( tmax <= t0 )
    {
      break;
    }
//
//  Otherwise, advance to time T1, and have RK4 estimate 
//  the solution U1 there.
//
    t1 = t0 + dt;
    u1 = rk4vec ( t0, n, u0, dt, rk4_f );
//
//  Shift the data to prepare for another step.
//
    t0 = t1;
    for ( i = 0; i < n; i++ )
    {
      u0[i] = u1[i];
    }
    delete [] u1;
  }


    // Assign output
    x1 = u0[0];
    v1 = u0[1];
    
  return;
}


//****************************************************************************80

double *rk4_f ( double t, int n, double u[] )

//****************************************************************************80
//
//  Purpose:
//
//    RK4_F evaluates the right hand side of a vector ODE.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//
//  Parameters:
//
//    Input, double T, the current time.
//
//    Input, int N, the dimension of the system.
//
//    Input, double U[N], the current solution value.
//
//    Output, double RK4_F[N], the value of the derivative, dU/dT.
//
{
  double *uprime;

  uprime = new double[n];

  uprime[0] =   u[1];
  uprime[1] = - u[0];
 
  return uprime;
}
