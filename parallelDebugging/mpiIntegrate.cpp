#include <iostream>
#include <mpi.h>
#include <stdlib.h>

double evalFxn(double pos, double leftBound, double rightBound, int *err)
{
  double eval=0.0;
  if ((pos >= leftBound) && (pos < 0.1))
    eval = -10.0*pos + 1;
  else if ((pos >= 0.1) && (pos <= 0.6))
    eval = 3.0*pos*pos - 2.0*pos + 0.17;
  else if ((pos > 0.6) && (pos <= rightBound))
    eval = -1.0/8.0 * (pos - 0.6) + 0.05;
  else {
    std::cout << "Error: You are trying to integrate between " << leftBound << " and " << rightBound << " but are attempting to eval at " << pos << std::endl;
    *err = 1;
  }
  return eval;
}

int main(int argc, char *argv[])
{
  int globalNumCells = 100;
  double leftBdry = 0.0;
  double rightBdry = 1.0;
  int mpi_err = 0;
  double localSum = 0.0;
  double globalSum;
  int numProcs, myRank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  //bool infLoop = true;

  //if (myRank == 7)
  //  while (infLoop);

  // Domain size covered by a processor
  double dProc = (rightBdry - leftBdry)/numProcs;
  
  // Domain size covered by a cell
  double dx = (rightBdry - leftBdry)/globalNumCells;

  // On each processor, take 1/numProcs of the domain
  // However, since you can't do a partial cell, round this
  int localNumCells = (int) ((float)globalNumCells/numProcs + 0.5);

  //std::cout << myRank << " " << localNumCells << " " << leftBdry + myRank*dProc << std::endl;

  for (int i = 0; i < localNumCells; i++)
  {
    // Find the midpoint of the cell
    double midpt = leftBdry + myRank*localNumCells*dx + i*dx + 0.5*dx;
    double fxnEval = evalFxn(midpt, leftBdry, rightBdry, &mpi_err);
    if (mpi_err == 1) MPI_Abort(MPI_COMM_WORLD, 0);
    // Midpoint rule, sum up midpoint * cell size
    localSum += fxnEval*dx;
  }

  // Sum across processors
  MPI_Reduce(&localSum,&globalSum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

  if (myRank == 0)
    std::cout << "The integral is " << globalSum << std::endl;

  MPI_Finalize();
  return 0;
}
