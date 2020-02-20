#include "rk4_data.hpp"

// Contructor
RK4Data::RK4Data ()
{
  // Default values
  m_id = 0;
  m_t0 = 0;
  m_stateVector0 = new double[2];
  m_stateVector0[0] = 0.0; // x0
  m_stateVector0[1] = 1.0; // v0
  m_tmax = 12.0;
  m_dt = 0.2;

  // Allocate output vector
  m_stateVector = new double[2];
}

RK4Data::RK4Data (int id, double t0, double x0, double v0, double tmax, double dt)
{
  // Assign values
  m_id = id;
  m_t0 = t0;
  m_stateVector0 = new double[2];
  m_stateVector0[0] = x0; 
  m_stateVector0[1] = v0;
  m_tmax = tmax;
  m_dt = dt;

  // Allocate output vector
  m_stateVector = new double[2];
}

// Destructor
RK4Data::~RK4Data()
{
  // Free Memory
  delete m_stateVector0;
  m_stateVector0 = 0;

  delete m_stateVector;
  m_stateVector = 0; 
}

// Setter/Getter
void RK4Data::getOutputStateVector(double & x, double & v)
{
  // Copy value of stateVector into x and v 
  x = m_stateVector[0];
  v = m_stateVector[1];
}

void RK4Data::setOutputStateVector(double x, double v)
{
  // Copy value of x and v into std::stateVector
  m_stateVector[0] = x;
  m_stateVector[1] = v;
}

int RK4Data::getId()
{
  return m_id;
}
  

void RK4Data::getAllData(double & t0, double & x, double & v, double & tmax, double & dt)
{
  // Copy all input
  t0 = m_t0;
  x = m_stateVector0[0];
  v = m_stateVector0[1];
  tmax = m_tmax;
  dt = m_dt;    
}

void RK4Data::getAllData(double * dataArray)
{
  // Copy all input
  dataArray[0] = m_t0;
  dataArray[1] = m_stateVector0[0];
  dataArray[2] = m_stateVector0[1];
  dataArray[3] = m_tmax;
  dataArray[4] = m_dt;    
}
