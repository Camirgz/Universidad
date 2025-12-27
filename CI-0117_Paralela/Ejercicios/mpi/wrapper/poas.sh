#!/bin/bash

#SBATCH --overcommit          # Allow more processes than CPUs per node
#SBATCH -J hello              # Job name
#SBATCH -o job.%j.txt         # Stdout output file (%j expands to jobId)
#SBATCH -N 7                  # Total number of nodes requested
#SBATCH -n 7                  # Total number of processes requested
#SBATCH -t 00:01:00           # Run time (hh:mm:ss) - 1 min
#SBATCH -p normal             # Partition to use (default, normal, debug)

prun bin/mpi_wrapper
