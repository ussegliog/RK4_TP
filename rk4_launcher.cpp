#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "rk4_API.hpp"
#include "rk4_IO.hpp"
#include "rk4_FIFO.hpp"


#ifdef WITH_MPI
#include "mpi.h"
#include "mpi_recv_rk4.hpp"
#include "mpi_send_rk4.hpp"
#endif

//****************************************************************************80

int main(int argc, char *argv[])

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

  
#ifdef WITH_MPI
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
#endif

  
  std::string inputTxt;
  std::string outputTxt;
  
  // Check and retrieve main inputs 
  if (argc != 3)
    {
      std::cout << "Wrong number of arguments (at least two with the input and output files)" <<
	std::endl;

      return 1;
    }
  else
    {
      inputTxt = std::string(argv[1]);
      outputTxt = std::string(argv[2]);
    }

  // Init some environment variables
  int world_size = 1;
  int rank = 0;
  char processor_name[1024];
  int name_len;
  
#ifdef WITH_MPI
  // Get the number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  // Get the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  // Get the name of the processor
  MPI_Get_processor_name(processor_name, &name_len);
#endif

  std::cout << "world_size : " << world_size << std::endl;
  std::cout << "rank : " << rank << std::endl;

  RK4FIFO * in_rk4Fifo = new RK4FIFO();
  RK4FIFO * out_rk4Fifo = new RK4FIFO();
  RK4IO * rk4IO;

  MPISend_RK4 * mpiSender;
  MPIRecv_RK4 * mpiRecver;

  // I/O only on rank = 0 and send data to other ranks
  if (rank == 0)
    {
      // Read input txt file
      rk4IO = new RK4IO(inputTxt, outputTxt);
      
      rk4IO->setInputFIFO(in_rk4Fifo);
      rk4IO->readInputFile();  

      std::vector<int> dest_processes;
      for (int i = 1; i < world_size; i++) 
	{
	  dest_processes.push_back(i);
	}
      dest_processes.push_back(0);
      
      mpiSender = new MPISend_RK4(in_rk4Fifo, &dest_processes, rank);
      mpiSender->sendDataToDestProcesses();      
      
      dest_processes.clear();
    }
  // If rank not 0 then receive rk4 data
  else
    {
      // From rank 0 only
      std::vector<int> src_processes;
      src_processes.push_back(0);

      mpiRecver = new MPIRecv_RK4(in_rk4Fifo, &src_processes, rank);
      mpiRecver->recvDataFromSrcProcesses();
    }

  int id = 0;
  double array [5];
  double x1, v1;
  double array_result [5];

  std::cout << "For Rank : " << rank << " FiFO In size : " << in_rk4Fifo->getSize() << std::endl;
  
  // Process rk4Data for current process
  while (in_rk4Fifo->getSize() > 0)
    {
      // Get elt
      in_rk4Fifo->getAndremoveData(id, array);
    
      // Process it
      rk4_API (id, array[0], array[1], array[2], array[3], array[4], x1, v1);

      // Assign results
      array_result[0] = array[0];
      array_result[1] = x1; // New X
      array_result[2] = v1; // New V
      array_result[3] = array[3];
      array_result[4] = array[4];
      
      // Add result into output FIFO
      out_rk4Fifo->addData(id, array_result);
    }
  
  std::cout << "For Rank : " << rank << " FiFO Out size : " << out_rk4Fifo->getSize() << std::endl;


  // Receive output RK4 data and I/O only on rank = 0 
  if (rank == 0)
    {
      // Receive data from all other processes
      std::vector<int> src_processes;
      for (int i = 1; i < world_size; i++) 
	{
	  src_processes.push_back(i);
	}
      mpiRecver = new MPIRecv_RK4(out_rk4Fifo, &src_processes, rank);
      mpiRecver->recvDataFromSrcProcesses();
      src_processes.clear();
      
      // Write ouput.txt
      rk4IO->setOutputFIFO(out_rk4Fifo);
      rk4IO->writeInputFile();
  
      //
      //  Terminate.

      delete rk4IO;
      rk4IO = 0;
    }
  // Send results to rank 0
  else
    {
      std::vector<int> dest_processes;
      dest_processes.push_back(0);
      
      mpiSender = new MPISend_RK4(out_rk4Fifo, &dest_processes, rank);
      mpiSender->sendDataToDestProcesses();      
      
      dest_processes.clear();
    }

  // Free Memory
  delete in_rk4Fifo;
  in_rk4Fifo = 0;
  delete out_rk4Fifo;
  out_rk4Fifo = 0;
  
  delete mpiSender;
  mpiSender = 0;
  delete mpiRecver;
  mpiRecver = 0;

#ifdef WITH_MPI
  // Finalize the MPI environment.
  MPI_Finalize();
#endif
  
  return 0;
}
