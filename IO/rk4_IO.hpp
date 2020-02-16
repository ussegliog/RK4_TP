# include <string>
# include <vector>

#include "rk4_FIFO.hpp"

#ifndef RK4_IO_H
#define RK4_IO_H

class RK4IO
{
public :
  // Constructor
  RK4IO (std::string inFilename, std::string outFilename); 

  // Destructor
  ~RK4IO();

  // IO functions
  int readInputFile();
  int writeInputFile();

  void setInputFIFO(RK4FIFO * rk4_FIFO);
  void setOutputFIFO(RK4FIFO * rk4_FIFO);
  
private :
  std::string m_inFilename;
  std::string m_outFilename;

  int m_counterData; // Count the number of RK4Data
  
  // FIFO (composition relations) 
  RK4FIFO * m_inputFIFO;
  RK4FIFO * m_outputFIFO;
};

#endif
