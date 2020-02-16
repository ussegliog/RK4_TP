# include "rk4_FIFO.hpp"

// Constructor
RK4FIFO::RK4FIFO()
{
  // Allocate the FIFO
  m_rk4Queue = new std::queue<RK4Data *>();
}

// Destructor
RK4FIFO::~RK4FIFO()
{
  // Free Memory
  while (!m_rk4Queue->empty()) 
    {
      // Free the front elt
      RK4Data * rk4data = m_rk4Queue->front();
      delete rk4data;
      m_rk4Queue->front() = 0;
      // erase the front
      m_rk4Queue->pop();
    }

  delete m_rk4Queue;
  m_rk4Queue = 0;
}


int RK4FIFO::getSize()
{
  return m_rk4Queue->size();
}

void RK4FIFO::addData(int rk4Id, double * rk4array)
{
  // Create a RK4Data with given id and array
  RK4Data * rk4Data = new RK4Data(rk4Id, rk4array[0], rk4array[1], rk4array[2],
				  rk4array[3], rk4array[4]);

  // Add it into the queue
  m_rk4Queue->push(rk4Data);
}


void RK4FIFO::getAndremoveData(int & rk4Id, double * rk4array)
{
  // Get one elt
  if (!m_rk4Queue->empty())
    {
      // Get the front elt
      RK4Data * rk4data = m_rk4Queue->front();
      // Fill arguments with it
      rk4Id = rk4data->getId();
      rk4data->getAllData(rk4array);
      // Free elt and erase the front
      delete rk4data;
      m_rk4Queue->front() = 0;
      // erase the front
      m_rk4Queue->pop(); 
    }
}
