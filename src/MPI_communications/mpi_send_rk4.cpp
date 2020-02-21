#include <cstdlib>
#include <cmath>
#include <cfenv> 
#include <iostream>

#include "mpi.h"

#include "mpi_send_rk4.hpp"

MPISend_RK4::MPISend_RK4(RK4FIFO * inFIFO, std::vector<int> * dest_processes, int rank)
{
  // Assign ptr (composition relations)
  m_inputFIFO = inFIFO;
 
  // Assign rank 
  m_rank = rank;

  // Check if destProcesses vector contains the rank of current process 
  // if yes, keep some data into inputFIFO (the last ones)
  // To do so, the current rank must the last one into the vector
  m_destProcesses = new std::vector<int>();
  // Copy elt and look if rank is in there
  bool rankIntoVect = false;
  for (int i = 0; i < dest_processes->size(); i++) 
    {
      // If rank, only set the boolean to true
      if (dest_processes->at(i) == rank)
	{
	  rankIntoVect = true;
	}
      // Else copy the rank
      else
	{
	  m_destProcesses->push_back(dest_processes->at(i));
	}
    }
  // If rank, set it in last position
  if (rankIntoVect)
    {
      m_destProcesses->push_back(rank);
    }
}

MPISend_RK4::~MPISend_RK4()
{
  // Free Memory
  m_destProcesses->clear();
  delete m_destProcesses;
  m_destProcesses = 0;
}

void MPISend_RK4::sendDataToDestProcesses()
{
  // Define chunk size
  // Avoid integer division and rounding to sup
  int chunkSize = std::lrint(static_cast<float>(m_inputFIFO->getSize())/m_destProcesses->size()); 
  int lastChunkSize = m_inputFIFO->getSize() - m_destProcesses->size()*chunkSize;

  if (m_destProcesses->size() == 1)
    {
      lastChunkSize = chunkSize;
    }

  // Arrays 
  int * rk4_id = new int[chunkSize]; // Maximum size = chunkSize
  int size_RK4Array = 5; // size for the array of a RK4Data 
  double * rk4_array = new double[chunkSize*size_RK4Array]; // Maximum size = chunkSize * size_RK4Array
  

  // Send RK4 Data to all dest processes
  for (int i = 0; i < m_destProcesses->size(); i++) 
    {
      // Check rank (if current rank => do not send data !) 
      if (m_destProcesses->at(i) != m_rank)
	{
	  // Get elts from inputFIFO (according to chunkSize or lastChunkSize)
	  int numberOfElts = chunkSize;
	  if (i ==  m_destProcesses->size() -1)
	    {
	      numberOfElts = lastChunkSize;
	    }
            
	  for (int j = 0; j < numberOfElts; j++) 
	    {
	      if (m_inputFIFO->getSize() > 0)
		{
		  // Get elt and fill id and array 
		  m_inputFIFO->getAndremoveData(rk4_id[j], &rk4_array[j*size_RK4Array]);
		}
	      else
		{
		  // Change the number of Elts
		  numberOfElts = j;
		  break;
		}
	    }

	  // Send size of the buffer 
	  MPI_Ssend(&numberOfElts, 1, MPI_INT, m_destProcesses->at(i), 0, MPI_COMM_WORLD);
	  if (numberOfElts > 0)
	    {
	      // Send elt in two parts : id then array
	      MPI_Ssend(rk4_id, numberOfElts, MPI_INT, m_destProcesses->at(i), 1, MPI_COMM_WORLD);
	      MPI_Ssend(rk4_array, numberOfElts*size_RK4Array, MPI_DOUBLE, m_destProcesses->at(i), 1, 
			MPI_COMM_WORLD);
	    }
	}
      
    }

  // Free Memory
  delete rk4_id;
  rk4_id = 0;
  delete rk4_array;
  rk4_array = 0;
}
