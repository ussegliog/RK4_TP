#!/bin/bash
# Directives PBS
#PBS -N jobMPI_RK4
#PBS -l select=8:ncpus=16:mpiprocs=16:mem=4000mb:os=rh7
#PBS -l place=free:group=switch
#PBS -l walltime=03:00:00
#PBS -o jobMPI_RK4.o
#PBS -e jobMPI_RK4.e

# Input Variables
# BIN_MPI
# INPUT_FILE
# OUTPUT_FILE

echo $BIN_MPI
echo $INPUT_FILE
echo $OUTPUT_FILE

if [ -z $BIN_MPI ]
then 
    echo "Please add the binary"
    exit 1
fi

if [ -z $INPUT_FILE ]
then 
    echo "Please add an input file"
    exit 1
fi

if [ -z $OUTPUT_FILE ]
then 
    echo "Please add an output file"
    exit 1
fi


#Chargement de l'environnement OpenMPI
module load openmpi

# nombre de processus MPI
nb_procs=128

echo $nb_procs

# Positionnement dans le répertoire de travail
cd "${PBS_O_WORKDIR}"

start=$SECONDS

# lancement du programme hybride OpenMP-MPI
mpirun -np ${nb_procs} --hostfile "${PBS_NODEFILE}" $BIN_MPI $INPUT_FILE $OUTPUT_FILE


end=$SECONDS

echo "duration: $((SECONDS-start)) seconds elapsed.."
