
#ifndef RK4_DATA_H
#define RK4_DATA_H

// Class to define data (one object = one line of input file)  
class RK4Data
{
public:
  // Constructors
  RK4Data (); // Default constructor
  RK4Data(int id, double t0, double x0, double v0, double tmax, double dt); 

  // Destructor
  ~RK4Data();
  
  // Setter/Getter
  void getOutputStateVector(double & x, double & v);
  void setOutputStateVector(double x, double v);

  int getId();
  // Get all inputs except id;
  void getAllData(double & t0, double & x, double & v, double & tmax, double & dt);
  void getAllData(double * dataArray);
  
private :
  // Inputs
  int m_id; // id of the object (for rk4 estimation)
  double m_t0; // t0 
  double * m_stateVector0; // Initial state vector (x0 and v0)
  double m_tmax; // time for end of RK4 calculation
  double m_dt; // Step for RK4 calculation
  
  // Outputs
  double * m_stateVector; // Estimated state vector (x and v) at tmax  
};

# endif
