# include <cmath>
# include <cstdlib>
# include <iomanip>
# include <iostream>

using namespace std;

# include "rk4_API.hpp"

//****************************************************************************80

int main ( ) 

//****************************************************************************80
//
//  Purpose:
// 
//    MAIN is the main program for RK4_LAUNCHER.
//
//  Discussion:
//
//    RK4_LAUNCHER executes the RK4 library with a defined API.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
{
  timestamp ( );
  cout << "\n";
  cout << "RK4_TEST\n";
  cout << "  C++ version\n";
  cout << "  Test the RK4 library.\n";

  // Test one object
  double dt = 0.2;
  int n = 2;
  double t0;
  double tmax = 12.0 * 3.141592653589793;
  double *u0;

  int id = 0;

  u0 = new double[n];
  u0[0] = 0.0;
  u0[1] = 1.0;

  t0 = 0.0;
  
  rk4_API (id, t0, u0, tmax, dt );
//
//  Terminate.
//
  cout << "\n";
  cout << "RK4_TEST\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  timestamp ( );

  return 0;
}
