#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, data;
    MPI_Init(&argc, &argv); // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the size (number of processes)

    if (rank == 0) {
        data = 100;
        printf("Process 0 broadcasting data %d to all processes\n", data);
    }

    // Broadcast data from process 0 to all other processes
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data %d\n", rank, data);

    MPI_Finalize(); // Finalize MPI
    return 0;
}
