#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function declarations
int generate_timestamps(double* time_stamps, int time_steps, double step_size);
void initialise_vector(double vector[], int size, double initial);
void print_vector(double vector[], int size);
int sum_vector(int vector[], int size);
void update_positions(double* positions, int points, double time);
double driver(double time);
void print_header(FILE** p_out_file, int points);

int main(int argc, char **argv)
{
    // Set default values for optional parameters
    int points = 0;
    int cycles = 5;
    int samples = 25;
    const char* output_file = "data/string_wave.csv";

    // Parse command-line arguments
    // Usage: ./bin/string_wave <points> [cycles] [samples] [output_file]
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <points> [cycles] [samples] [output_file]\n", argv[0]);
        exit(1);
    }
    points = atoi(argv[1]);
    if (argc >= 3)
        cycles = atoi(argv[2]);
    if (argc >= 4)
        samples = atoi(argv[3]);
    if (argc >= 5)
        output_file = argv[4];

    int time_steps = cycles * samples + 1;
    double step_size = 1.0 / samples;

    // Allocate and initialise the time stamps vector
    double* time_stamps = (double*) malloc(time_steps * sizeof(double));
    initialise_vector(time_stamps, time_steps, 0.0);
    generate_timestamps(time_stamps, time_steps, step_size);

    // Allocate and initialise the positions vector
    double* positions = (double*) malloc(points * sizeof(double));
    initialise_vector(positions, points, 0.0);

    // Open the output file for writing
    FILE* out_file = fopen(output_file, "w");
    if (out_file == NULL) {
        perror("Error opening output file");
        exit(1);
    }
    print_header(&out_file, points);

    // Run the simulation over each time step
    for (int i = 0; i < time_steps; i++) {
        update_positions(positions, points, time_stamps[i]);
        fprintf(out_file, "%d, %lf", i, time_stamps[i]);
        for (int j = 0; j < points; j++) {
            fprintf(out_file, ", %lf", positions[j]);
        }
        fprintf(out_file, "\n");
    }

    // Clean up
    free(time_stamps);
    free(positions);
    fclose(out_file);
    return 0;
}

// prints a header to the file
void print_header(FILE** p_out_file, int points)
{
    fprintf(*p_out_file, "#, time");
    for (int j = 0; j < points; j++) {
        fprintf(*p_out_file, ", y[%d]", j);
    }
    fprintf(*p_out_file, "\n");
}

// simple harmonic oscillator driving function
double driver(double time)
{
    return sin(time * 2.0 * M_PI);
}

// update positions based on the driver function and previous positions
void update_positions(double* positions, int points, double time)
{
    double* new_positions = (double*) malloc(points * sizeof(double));
    new_positions[0] = driver(time);
    for (int i = 1; i < points; i++) {
        new_positions[i] = positions[i - 1];
    }
    for (int i = 0; i < points; i++) {
        positions[i] = new_positions[i];
    }
    free(new_positions);
}

// sums the elements of a vector (not used in main)
int sum_vector(int vector[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += vector[i];
    }
    return sum;
}

// initialises all elements in a vector to a given initial value
void initialise_vector(double vector[], int size, double initial)
{
    for (int i = 0; i < size; i++) {
        vector[i] = initial;
    }
}

// prints a vector of doubles (not used in main)
void print_vector(double vector[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d, %lf\n", i, vector[i]);
    }
}

// generates time stamps; a dummy implementation if not provided
int generate_timestamps(double* time_stamps, int time_steps, double step_size)
{
    for (int i = 0; i < time_steps; i++) {
        time_stamps[i] = i * step_size;
    }
    return 0;
}
