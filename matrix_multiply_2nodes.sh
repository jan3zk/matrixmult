#!/bin/bash
#SBATCH --reservation=EuroCC2
#SBATCH --output=matrix_multiply.out
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=128

srun --ntasks=1 --nodes=1 --exclusive ./matrix_multiply 2500 A1 B1 &
srun --ntasks=1 --nodes=1 --exclusive ./matrix_multiply 2500 A2 B2 &

wait
