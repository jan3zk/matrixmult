# Parallel Matrix Multiplication

This repository contains a set of programs for creating and multiplying large matrices using parallel processing capabilities on a high-performance computing (HPC) cluster using SLURM workload manager.

## Overview

The project consists of two main components:
1. A matrix creation program that generates random matrices
2. A parallel matrix multiplication program that utilizes OpenMP for computation

## Components

- `matrix_create.c` - Program to generate random matrices
- `matrix_multiply.c` - OpenMP-enabled matrix multiplication program
- `matrix_multiply.sh` - SLURM script for single-node execution
- `matrix_multiply_2nodes.sh` - SLURM script for dual-node parallel execution

## Prerequisites

- GCC compiler with OpenMP support
- SLURM workload manager
- Access to an HPC cluster
- SSH access to the cluster

## Compilation

To compile the programs, use the following commands:

```bash
# Compile matrix creation program
gcc -o matrix_create matrix_create.c

# Compile matrix multiplication program with OpenMP support
gcc -fopenmp -o matrix_multiply matrix_multiply.c
```

## Usage

### 1. Creating Matrices

Generate four random matrices (A1, B1, A2, B2) of specified size:

```bash
./matrix_create <matrix_size>

# Example for 2500x2500 matrices
./matrix_create 2500
```

### 2. Matrix Multiplication

You can run matrix multiplication in two modes:

#### Single Node

```bash
sbatch matrix_multiply.sh
```
This will multiply matrices A1 and B1 using 64 CPU cores on a single node.

#### Dual Node

```bash
sbatch matrix_multiply_2nodes.sh
```
This will perform two matrix multiplications in parallel:
- A1 × B1 on the first node
- A2 × B2 on the second node

### Monitoring Jobs

To monitor your running jobs:
```bash
# Watch job queue
watch -n 1 squeue --user=$USER

# View job output
cat matrix_multiply.out

# View detailed job information
sacct -j <JOB_ID> --format=JobID,Start,End,Elapsed,REQCPUS,ALLOCTRES%30
```

## SLURM Configuration

The SLURM scripts are configured with the following specifications:

### Single Node (`matrix_multiply.sh`)
- 1 node
- 1 task
- 64 CPUs per task
- 1-minute time limit

### Dual Node (`matrix_multiply_2nodes.sh`)
- 2 nodes
- 2 tasks (1 per node)
- 64 CPUs per task
- Runs two matrix multiplications in parallel

## Output

The multiplication results are saved in binary files:
- For single node: `A1B1`
- For dual nodes: `A1B1` and `A2B2`

The execution time is written to `matrix_multiply.out`.

## Additional Commands

For system monitoring and resource management:

```bash
# Show node reservations
sinfo -l -N -R delavnica

# Show detailed node information
scontrol show node <nodename>
```
