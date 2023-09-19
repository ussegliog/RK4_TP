#!/bin/bash

#SBATCH --job-name=jobMPI_RK4       # job's name
# --output = name of the output file  --error= name of error file (%j = jobID )
#SBATCH --output=jobMPI_RK4-%j.out
#SBATCH --error=jobMPI_RK4-%j.err
#SBATCH -N 4                        # number of nodes (or --nodes=1)
##SBATCH -n 16                        # number of tasks (or --tasks=16) in total 
#SBATCH --ntasks-per-node 16
#SBATCH --mem-per-cpu=8000M         # memory per core
#SBATCH --time=00:30:00             # Wall Time 30mn
#SBATCH --account=cnes_level2       # MANDATORY : account  ( launch myaccounts to list your accounts)
##SBATCH --export=none               # To start the job with a clean environnement and source of ~/.bashrc



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


# Chargement de l'environnement OpenMPI
module load openmpi

# The following command is mandatory with --export=none option for multinodes jobs
unset SLURM_EXPORT_ENV


# Positionnement dans le répertoire de travail
cd "${SLURM_SUBMIT_DIR}"

start=$SECONDS

# lancement du programme hybride OpenMP-MPI
srun $BIN_MPI $INPUT_FILE $OUTPUT_FILE


end=$SECONDS

echo "duration: $((SECONDS-start)) seconds elapsed.."
