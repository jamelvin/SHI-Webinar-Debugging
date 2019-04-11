module purge

module load pecos
module load c7
module load intel/17.0
module load mpich2/3.1.4

echo "icc -g -o raceThread raceThread.c -fopenmp"
