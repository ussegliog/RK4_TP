#include <cstdlib>
#include <iostream>

#include "mpi.h"

#include "mpi_recv_rk4.hpp"

MPIRecv_RK4::MPIRecv_RK4(RK4FIFO * outFIFO, std::vector<int> * src_processes, int rank)
{
  // Assign ptr (composition relations)
  m_outputFIFO = outFIFO;
 
  // Assign rank 
  m_rank = rank;

  // Check if src_processes vector contains the rank of current process 
  // if yes, keep some data into inputFIFO (the last ones)
  // To do so, the current rank must be the first one into the vector
  m_srcProcesses = new std::vector<int>();
  // Copy elt and look if rank is in there
  bool rankIntoVect = false;
  for (int i = 0; i < src_processes->size(); i++) 
    {
      // If rank, only set the boolean to true
      if (src_processes->at(i) == rank)
	{
	  rankIntoVect = true;
	}
    }
  // If rank, set it in first position
  if (rankIntoVect)
    {
      m_srcProcesses->push_back(rank);
    }
  for (int i = 0; i < src_processes->size(); i++) 
    {
      // If not rank, copy it
      if (src_processes->at(i) != rank)
	{
	  m_srcProcesses->push_back(src_processes->at(i));
	}
   }
}

MPIRecv_RK4::~MPIRecv_RK4()
{
  // Free Memory
  m_srcProcesses->clear();
  delete m_srcProcesses;
  m_srcProcesses = 0;
}

void MPIRecv_RK4::recvDataFromSrcProcesses()
{
  MPI_Status status;
  int * rk4_id;
  double * rk4_array;
  int size_RK4Array = 5;

  for (int i = 0; i < m_srcProcesses->size(); i++) 
    {
      // Retrieve the size of data from current src process
      int numberOfElts = 0;
      MPI_Recv(&numberOfElts, 1, MPI_INT, m_srcProcesses->at(i), 0, MPI_COMM_WORLD, &status);
    
      // Allocation for rk4_id and rk4_array accoding to the numberOfElts
      rk4_id = new int[numberOfElts];
      rk4_array = new double[size_RK4Array*numberOfElts];

      // Receive data for src process in two parts : id then array
      MPI_Recv(rk4_id, numberOfElts, MPI_INT, m_srcProcesses->at(i), 1, MPI_COMM_WORLD, &status);
      MPI_Recv(rk4_array, numberOfElts*size_RK4Array, MPI_DOUBLE, m_srcProcesses->at(i), 1, 
	       MPI_COMM_WORLD, &status);
      
      // Add elts into the outputFIFO : one by one
      for (int j = 0; j < numberOfElts; j++) 
	{
	  m_outputFIFO->addData(rk4_id[j], &rk4_array[j*size_RK4Array]);
	}

      // Free Memory
      delete rk4_id;
      rk4_id = 0;
      delete rk4_array;
      rk4_array = 0;
    }
}
