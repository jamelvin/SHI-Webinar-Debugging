#include <iostream>
#include <mpi.h>

double evalFxn(double pos, double leftBound, double rightBound)
{
  double eval;
  if ((pos >= leftBound) && (pos < 0.1))
    eval = -10.0*pos + 1;
  else if ((pos >= 0.1) && (pos <= 0.6))
    eval = 3.0*pos*pos - 2.0*pos + 0.17;
  else if ((pos > 0.6) && (pos <= rightBound))
    eval = 1.0/8.0 * (pos - 0.6) + 0.05;
  else
    std::cout << "Error: You are trying to integrate between " << leftBound << " and " << rightBound << " but are attempting to eval at " << pos << std::endl;
  return eval;
}

int main(int argc, char *argv[])
{
  int globalNumCells = 100;
  double leftBdry = 0.0;
  double rightBdry = 1.0;

  double localSum = 0.0;
  double globalSum;
  int numProcs, myRank;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  double dProc = (rightBdry - leftBdry)/numProcs;
  double dx = (rightBdry - leftBdry)/globalNumCells;
  int localNumCells = (int) ((float)globalNumCells/numProcs + 0.5);

  for (int i = 0; i < localNumCells; i++)
  {
    double midpt = leftBdry + myRank*dProc + i*dx + 0.5*dx;
    double fxnEval = evalFxn(midpt, leftBdry, rightBdry);
    localSum += fxnEval;
  }

  MPI_Reduce(&localsum,&globalsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

  if (myRank == 0)
    std::cout << "The integral is " << globalSum << std::endl;

  return 0;
}
