#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int ierr, myid, numprocs;
  int ghostSize = 1;
  int gridSize = 8;

  MPI_Status stat;
  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // neighbor ids for domain decomposition
  //nbrid[0] = myid - 1;
  //if (myid == 0) nbrid[0] = numprocs-1;
  //nbrid[1] = myid + 1;
  //if (myid == numprocs-1) nbrid[1] = 0;

  double *phi = new double[gridSize + 2*ghostSize];
  
  // Creating buffers for send and receive
  double *bufSend = new double[ghostSize];
  double *bufRecv = new double[ghostSize];

  for (int i=ghostSize; i < ghostSize + gridSize; ++i) {
    phi[i] = myid;
  }
  
  // first store the ghost cells in the lower direction
  for (int i=ghostSize; i < 2*ghostSize; ++i) {
    int ind = i - ghostSize;
    xbufSend[ind] = phi[i];
  }

  // send to lower and recv from upper
  MPI_Send(bufSend, nGuard, MPI_DOUBLE, myid-1, 111, MPI_COMM_WORLD); 
  MPI_Recv(bufRecv, nGuard, MPI_DOUBLE, myid+1, 111, MPI_COMM_WORLD, &stat); 

  // what you received from the lower nbr, put it in phi
  for (int i=0; i < nGuard; ++i) {
    int ind = ghostSize + gridSize + i;
    phi[ind] = xbufRecv[i];
  }

  //prepare the ghost cells to be sent in upper direction
  for (int i=gridSize; i < ghostSize+gridSize; ++i) {
    int ind = i - gridSize;
    xbufSend[ind] = phi[i];
  }

  // send to upper and recv from the lower neighbor
  MPI_Send(xbufSend, ySize*nGuard, MPI_DOUBLE, myid+1, 222, MPI_COMM_WORLD);
  MPI_Recv(xbufRecv, ySize*nGuard, MPI_DOUBLE, myid-1, 222, MPI_COMM_WORLD, &stat);

  // now put the received ghost cells from the right into the upper guard cells
  for (int i=gridSize + ghostSize; i < gridSize + 2*ghostSize; ++i) {
      ind = i - ghostSize+gridSize;
      phi[i] = xbufRecv[ind];
  }

  std::cont << "On processor " << myid << std::endl;
  for (i=0; i < 2*ghostSize + gridSize; ++i) 
    std::cout << phi[i] << " ";
  std::cout << std::endl;

  delete[] phi;
  delete[] bufSend;
  delete[] bufRecv;

  MPI_Finalize();

  return 0;
}
