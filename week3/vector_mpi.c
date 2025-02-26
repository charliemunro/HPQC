#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void vector_addition(int *vector, int size, int rank, int num_procs) {
    int chunk_size = size / num_procs;
    int start = rank * chunk_size;
    int end = (rank == num_procs - 1) ? size : (rank + 1) * chunk_size;
    int local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += vector[i];
    }

    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of vector elements: %d\n", global_sum);
    }
}

int main(int argc, char *argv[]) {
    int rank, num_procs;
    int size = atoi(argv[1]);
    int *vector = (int*)malloc(size * sizeof(int));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Initialize vector with random values
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            vector[i] = rand() % 100;  // Random values between 0-99
        }
    }

    MPI_Bcast(vector, size, MPI_INT, 0, MPI_COMM_WORLD);  // Broadcast the vector

    vector_addition(vector, size, rank, num_procs);

    MPI_Finalize();
    free(vector);
    return 0;
}
