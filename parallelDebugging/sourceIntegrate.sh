module purge

module load pecos
module load c7
module load intel/17.0
module load mpich2/3.1.4

echo "icc -g -o mpiIntegrate mpiIntegrate.cpp -I/opt/apps/ossw/libraries/mpich2/mpich2-3.1.4/c7/intel-17.0/include -L//opt/apps/ossw/libraries/mpich2/mpich2-3.1.4/c7/intel-17.0/lib -lmpi"
