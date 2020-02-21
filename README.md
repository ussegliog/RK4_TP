# RK4_TP
Example of MPI code for a runge kutta estimation

This code uses a RK4 implementation (from https://people.sc.fsu.edu/~jburkardt/cpp_src/rk4/rk4.html) to approximate a ODE calculation.

## Installation
To install this application, seraval requirements are necessary :
* A MPI implementation such as OPENMPI, intelMPI, MPICH ... to use MPI execution or a simple compiler (ex:GNU) for a execution without MPI 
* A cmake installation

With theses requirements, you can install the application by following the differents points below :
* Configure the project :
  * Create a build directory at the root 
  * Go to this repository
  * Launch cmake command : 
    * **CXX=<path_to_MPI_implementation>/bin/mpic++ cmake -DWITH_MPI=ON ../src** for MPI execution
    * **CXX=<path_to_GNU>/bin/g++ cmake -DWITH_MPI=OFF ../src** otherwise
* Compile : **make** command into build repository
* Installation : **make install**. The parameter -DCMAKE_INSTALL_PREFIX=<install_directory> can be added into the previous cmake to indiquate an installation directory
  
Once the installation over, you can launch an execution with defined input/output with :
* **mpirun -np -np ${nb_procs} --hostfile "${hostFile}" rk4Launcher $INPUT_FILE $OUTPUT_FILE** for a MPI execution
* **./rk4Launcher $INPUT_FILE $OUTPUT_FILE** otherwise

Two bash scripts are available into scripts/ directory to show how to configure automacally the project and to launch on a cluster, a MPI execution. 

## Input/Output

Two files are used as input and output. Each files are in txt format and contains for each line data/objet named RK4Data. 
A RK4Data is composed of :
* An id
* An array with 5 values : intial_time, x0 (position), v0 (velocity), last_time, time_step

At the end of the execution, an output file is created with the same shape and updates the values for position and velocity estimated at the **last_time**.

# Src files
All sources are contained into src directory. 
