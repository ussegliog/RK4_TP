# include <cmath>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <string>

# include "rk4_API.hpp"
# include "rk4_IO.hpp"
# include "rk4_FIFO.hpp"

#ifdef WITH_MPI
#include "mpi.h"
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

  if (rank == 0)
    {
      // Read input txt file
      RK4IO * rk4IO = new RK4IO(inputTxt, outputTxt);
      RK4FIFO * in_rk4Fifo = new RK4FIFO();
      RK4FIFO * out_rk4Fifo = new RK4FIFO();

      rk4IO->setInputFIFO(in_rk4Fifo);
      rk4IO->readInputFile();  

      int id = 0;
      double array [5];
      double x1, v1;
      double array_result [5];
  
      // Process all rk4Data
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

      // Write ouput.txt
      rk4IO->setOutputFIFO(out_rk4Fifo);
      rk4IO->writeInputFile();
  
      //
      //  Terminate.

      delete rk4IO;
      rk4IO = 0;
    }
  
#ifdef WITH_MPI
  // Finalize the MPI environment.
  MPI_Finalize();
#endif
  
  return 0;
}
