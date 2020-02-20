#include <string>
#include <vector>

#include "rk4_FIFO.hpp" 


#ifndef MPIRECV_RK4_H
#define MPIRECV_RK4_H


// Class that handles main communications between processes by encapsulating MPI_RECV calls
class MPIRecv_RK4
{
public :
  // Constructor
  MPIRecv_RK4(RK4FIFO * inFIFO, std::vector<int> * dest_processes, int rank); 

  // Destructor
  ~MPIRecv_RK4();

  // receive functions : Get the data included into FIFO from src processes by separating data in chunks 
  // chunk size = inputFIFO.size() / NbDestProcesses
  void recvDataFromSrcProcesses();
  
private :
  // FIFO (composition relation) 
  RK4FIFO * m_outputFIFO;

  // Vector of src processes 
  std::vector<int> * m_srcProcesses;

  // Rank of current process
  int m_rank;

};

#endif
