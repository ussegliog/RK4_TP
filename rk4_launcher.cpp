# include <cmath>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <string>

using namespace std;

# include "rk4_API.hpp"
# include "rk4_IO.hpp"
# include "rk4_FIFO.hpp"

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
  std::string inputTxt;
  std::string outputTxt;
  
  // Check main inputs
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

  
  timestamp ( );
  cout << "\n";
  cout << "RK4_TEST\n";
  cout << "  C++ version\n";
  cout << "  Test the RK4 library.\n";  
  

  // Read input txt file
  RK4IO * rk4IO = new RK4IO(inputTxt, outputTxt);
  RK4FIFO * in_rk4Fifo = new RK4FIFO();
  RK4FIFO * out_rk4Fifo = new RK4FIFO();

  std::cout << "Size of FIFO : " << in_rk4Fifo->getSize() << std::endl;
  
  rk4IO->setInputFIFO(in_rk4Fifo);
  rk4IO->readInputFile();

  std::cout << "Size of FIFO : " << in_rk4Fifo->getSize() << std::endl;
  

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
//
  cout << "\n";
  cout << "RK4_TEST\n";
  cout << "  Normal end of execution.\n";
  cout << "\n";
  timestamp ( );

  delete rk4IO;
  rk4IO = 0;
  
  return 0;
}
