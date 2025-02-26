#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vector_addition(int *vector, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += vector[i];
    }
    printf("Sum of vector elements: %d\n", sum);
}

int main(int argc, char *argv[]) {
    int size = atoi(argv[1]);
    int *vector = (int*)malloc(size * sizeof(int));
    // Initialize vector with random values
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;  // Random values between 0-99
    }

    clock_t start = clock();
    vector_addition(vector, size);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);

    free(vector);
    return 0;
}
