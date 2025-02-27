#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

// Function declarations
int generate_timestamps(double* time_stamps, int time_steps, double step_size);
void initialise_vector(double vector[], int size, double initial);
void print_header(FILE **p_out_file, int points);
double driver(double time);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Usage: ./bin/string_wave_mpi <points> <cycles> <samples> <output_file>
    if (argc < 5) {
        if (rank == 0)
            fprintf(stderr, "Usage: %s <points> <cycles> <samples> <output_file>\n", argv[0]);
        MPI_Finalize();
        exit(1);
    }
    
    int points = atoi(argv[1]);    // Total number of points on the string
    int cycles = atoi(argv[2]);    // Number of cycles to simulate
    int samples = atoi(argv[3]);   // Samples per cycle
    const char *output_file = argv[4];

    // Ensure points is divisible by the number of processes
    if (points % size != 0) {
        if (rank == 0)
            fprintf(stderr, "Error: points (%d) must be divisible by number of processes (%d).\n", points, size);
        MPI_Finalize();
        exit(1);
    }
    int local_points = points / size;
    
    int time_steps = cycles * samples + 1;
    double step_size = 1.0 / samples;

    // Allocate and initialize time stamps
    double* time_stamps = (double*) malloc(time_steps * sizeof(double));
    initialise_vector(time_stamps, time_steps, 0.0);
    generate_timestamps(time_stamps, time_steps, step_size);

    // Allocate and initialize local positions array
    double* local_positions = (double*) malloc(local_points * sizeof(double));
    initialise_vector(local_positions, local_points, 0.0);

    // Only rank 0 opens the output file and writes the header
    FILE* out_file = NULL;
    if (rank == 0) {
        out_file = fopen(output_file, "w");
        if (out_file == NULL) {
            perror("Error opening output file");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        print_header(&out_file, points);
    }
    
    // Allocate an array for gathering global positions at rank 0
    double* global_positions = NULL;
    if (rank == 0) {
        global_positions = (double*) malloc(points * sizeof(double));
    }

    // Start overall simulation timing
    double t_total_start = MPI_Wtime();

    // Simulation loop
    for (int t = 0; t < time_steps; t++) {
        double t_iter_start = MPI_Wtime(); // Start iteration timer

        // Communication: exchange boundary info
        double boundary;
        if (rank > 0) {
            MPI_Recv(&boundary, 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        double t_comm_start = MPI_Wtime(); // Start communication timer

        // Create new local positions array
        double* new_local = (double*) malloc(local_points * sizeof(double));
        if (rank == 0) {
            new_local[0] = driver(time_stamps[t]);
        } else {
            new_local[0] = boundary;
        }
        for (int i = 1; i < local_points; i++) {
            new_local[i] = local_positions[i - 1];
        }

        // Send the last element to the next process if applicable
        if (rank < size - 1) {
            MPI_Send(&local_positions[local_points - 1], 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
        }

        double t_comm_end = MPI_Wtime(); // End communication timer

        // Update local positions with new values
        for (int i = 0; i < local_points; i++) {
            local_positions[i] = new_local[i];
        }
        free(new_local);

        // Gather all local positions to rank 0
        MPI_Gather(local_positions, local_points, MPI_DOUBLE,
                   global_positions, local_points, MPI_DOUBLE,
                   0, MPI_COMM_WORLD);

        double t_iter_end = MPI_Wtime(); // End iteration timer

        // Rank 0 writes the current time step and full positions to file
        if (rank == 0) {
            fprintf(out_file, "%d, %lf", t, time_stamps[t]);
            for (int i = 0; i < points; i++) {
                fprintf(out_file, ", %lf", global_positions[i]);
            }
            fprintf(out_file, "\n");

            // Optionally print timing information for this iteration
            printf("Iteration %d: Total = %lf sec, Comm = %lf sec, Computation = %lf sec\n",
                   t,
                   t_iter_end - t_iter_start,
                   t_comm_end - t_comm_start,
                   (t_iter_end - t_iter_start) - (t_comm_end - t_comm_start));
        }
    }

    double t_total_end = MPI_Wtime();
    if (rank == 0) {
        printf("Total simulation time: %lf seconds\n", t_total_end - t_total_start);
    }

    // Clean up
    free(time_stamps);
    free(local_positions);
    if (rank == 0) {
        free(global_positions);
        fclose(out_file);
    }

    MPI_Finalize();
    return 0;
}

// Prints a header line into the CSV file
void print_header(FILE **p_out_file, int points)
{
    fprintf(*p_out_file, "#, time");
    for (int j = 0; j < points; j++) {
        fprintf(*p_out_file, ", y[%d]", j);
    }
    fprintf(*p_out_file, "\n");
}

// Defines the simple harmonic oscillator driving function
double driver(double time)
{
    return sin(time * 2.0 * M_PI);
}

// Initializes a vector to a given value
void initialise_vector(double vector[], int size, double initial)
{
    for (int i = 0; i < size; i++) {
        vector[i] = initial;
    }
}

// Generates time stamps given the total number of steps and step size
int generate_timestamps(double* time_stamps, int time_steps, double step_size)
{
    for (int i = 0; i < time_steps; i++) {
        time_stamps[i] = i * step_size;
    }
    return 0;
}
