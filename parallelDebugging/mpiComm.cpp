// This file should create an array of size (gridSize) and populate it with the 
// processor ID.  The array will also contain buffer cells of size (ghostSize), 
// at the beginning and end of the array.  Using MPI, each processor should 
// communicate with it's neighbor to populate the ghost cell array.
//
// Finally, each processor should dump its array to a file (myid.txt)

#include <iostream>
#include <math.h>
#include <mpi.h>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{
  int ierr, myid, numprocs;
  int ghostSize = 1;
  int gridSize = 8;
  //int nbrid[2];

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
    bufSend[ind] = phi[i];
  }

  // send to lower and recv from upper
  MPI_Send(bufSend, ghostSize, MPI_DOUBLE, myid-1, 111, MPI_COMM_WORLD); 
  MPI_Recv(bufRecv, ghostSize, MPI_DOUBLE, myid+1, 111, MPI_COMM_WORLD, &stat); 

  // what you received from the lower nbr, put it in phi
  for (int i=0; i < ghostSize; ++i) {
    int ind = ghostSize + gridSize + i;
    phi[ind] = bufRecv[i];
  }

  //prepare the ghost cells to be sent in upper direction
  for (int i=gridSize; i < ghostSize+gridSize; ++i) {
    int ind = i - gridSize;
    bufSend[ind] = phi[i];
  }

  // send to upper and recv from the lower neighbor
  MPI_Send(bufSend, ghostSize, MPI_DOUBLE, myid+1, 222, MPI_COMM_WORLD);
  MPI_Recv(bufRecv, ghostSize, MPI_DOUBLE, myid-1, 222, MPI_COMM_WORLD, &stat);

  // now put the received ghost cells from the right into the lower guard cells
  for (int i=gridSize + ghostSize; i < gridSize + 2*ghostSize; ++i) {
      int ind = i - ghostSize+gridSize;
      phi[ind] = bufRecv[i];
  }

  std::ofstream myfile;
  std::ostringstream fnameStream("xxxxx");
  fnameStream << myid << ".txt";
  std::string fname = fnameStream.str();
  myfile.open(fname.c_str());
  myfile << "On processor " << myid << std::endl;
  for (int i=0; i < 2*ghostSize + gridSize; ++i) 
    myfile << phi[i] << " ";
  myfile << std::endl;

  myfile.close();

  delete[] phi;
  delete[] bufSend;
  delete[] bufRecv;

  MPI_Finalize();

  return 0;
}
