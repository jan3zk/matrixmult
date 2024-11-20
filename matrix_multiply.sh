#!/bin/bash
#SBATCH --reservation=delavnica
#SBATCH --output=matrix_multiply.out
#SBATCH --time=00:01:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=128

srun --ntasks=1 --nodes=1 --exclusive ./matrix_multiply 5000 A1 B1

wait
