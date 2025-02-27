#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16  // Vector size

void initialize_array(int *array, int size) {
    for (int i = 0; i < size; i++)
        array[i] = i + 1;
}

int main(int argc, char** argv) {
    int rank, size, local_sum = 0, global_sum = 0;
    int *array = NULL;
    int local_N;
    double start_time, end_time;  // Declare here ONCE

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_N = N / size;
    int *local_array = (int*)malloc(local_N * sizeof(int));

    if (rank == 0) {
        array = (int*)malloc(N * sizeof(int));
        initialize_array(array, N);
    }

    // MPI_Scatter: Distribute data to processes
    MPI_Scatter(array, local_N, MPI_INT, local_array, local_N, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_N; i++)
        local_sum += local_array[i];

    // Measure time for MPI_Gather
    start_time = MPI_Wtime();
    MPI_Gather(&local_sum, 1, MPI_INT, array, 1, MPI_INT, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    if (rank == 0)
        printf("MPI_Gather Time: %f seconds\n", end_time - start_time);

    // Measure time for MPI_Reduce
    start_time = MPI_Wtime();
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    if (rank == 0)
        printf("MPI_Reduce Time: %f seconds\n", end_time - start_time);

    if (rank == 0) free(array);
    free(local_array);
    MPI_Finalize();
    return 0;
}
