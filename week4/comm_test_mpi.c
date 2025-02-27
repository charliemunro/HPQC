#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void initialize_mpi(int *rank, int *size) {
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);
}

void communicate(int rank, int size) {
    int data = 10;
    MPI_Status status;
    double start_time, end_time;

    if (rank == 1) {
        start_time = MPI_Wtime();

        // ===== Uncomment ONE of the following send types at a time =====

        // Standard Send
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
        // Synchronous Send
        // MPI_Ssend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
        // Buffered Send (Requires buffer allocation)
        // int buf_size = MPI_BSEND_OVERHEAD + sizeof(int);
        // void *buffer = malloc(buf_size);
        // MPI_Buffer_attach(buffer, buf_size);
        // MPI_Bsend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        // MPI_Buffer_detach(&buffer, &buf_size);
        
        // Ready Send (Receiver MUST be ready before calling this)
        // MPI_Rsend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        
        // Non-blocking Send
        // MPI_Request request;
        // MPI_Isend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        // MPI_Wait(&request, &status);

        end_time = MPI_Wtime();
        printf("Hello, I am %d of %d. Sent %d to Rank 0 in %f seconds\n", rank, size, data, end_time - start_time);
    } else if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        end_time = MPI_Wtime();
        printf("Hello, I am %d of %d. Received %d from Rank 1 in %f seconds\n", rank, size, data, end_time - start_time);
    }
}

void finalize_mpi() {
    MPI_Finalize();
}

int main() {
    int rank, size;
    initialize_mpi(&rank, &size);
    communicate(rank, size);
    finalize_mpi();
    return 0;
}
