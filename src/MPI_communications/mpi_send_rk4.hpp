#include <string>
#include <vector>

#include "rk4_FIFO.hpp" 


#ifndef MPISEND_RK4_H
#define MPISEND_RK4_H


// Class that handles main communications between processes by encapsulating MPI_SEND calls
class MPISend_RK4
{
public :
  // Constructor
  MPISend_RK4(RK4FIFO * inFIFO, std::vector<int> * dest_processes, int rank); 

  // Destructor
  ~MPISend_RK4();

  // Send functions : Send the data included into FIFO to dest processes by separating data in chunks 
  // chunk size = inputFIFO.size() / NbDestProcesses
  void sendDataToDestProcesses();
  
private :
  // FIFO (composition relation) 
  RK4FIFO * m_inputFIFO;

  // Vector of dest processes (composition)
  std::vector<int> * m_destProcesses;

  // Rank of current process
  int m_rank;

};

#endif
