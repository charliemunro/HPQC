#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_PINGS 1000  // Number of messages sent back and forth

int main(int argc, char** argv) {
    int rank, size, data_size;
    double start_time, end_time;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            printf("This program must be run with exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (argc < 2) {
        if (rank == 0) {
            printf("Usage: mpirun -np 2 ./bin/pingpong [data_size_in_bytes]\n");
        }
        MPI_Finalize();
        return 1;
    }

    data_size = atoi(argv[1]);  // Read data size from command-line argument
    char* buffer = (char*)malloc(data_size);  // Allocate array of given size

    if (rank == 0) {
        start_time = MPI_Wtime();
        for (int i = 0; i < NUM_PINGS; i++) {
            MPI_Send(buffer, data_size, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer, data_size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &status);
        }
        end_time = MPI_Wtime();

        double total_time = end_time - start_time;
        double avg_time_per_round_trip = total_time / NUM_PINGS;
        double bandwidth = (data_size * 2.0) / (avg_time_per_round_trip * 1e6);  // MB/s

        printf("Data Size: %d bytes | Total Time: %.9f sec | Bandwidth: %.2f MB/s\n",
               data_size, total_time, bandwidth);
    } else if (rank == 1) {
        for (int i = 0; i < NUM_PINGS; i++) {
            MPI_Recv(buffer, data_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Send(buffer, data_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
        }
    }

    free(buffer);
    MPI_Finalize();
    return 0;
}
