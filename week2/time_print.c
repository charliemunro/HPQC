#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    FILE *file;

    file = fopen("output_c.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    start = clock(); // Start timing

    for (int i = 0; i < 1000000; i++) {
        fprintf(file, "Line %d\n", i);
    }

    end = clock(); // End timing
    fclose(file);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("C File Write Time: %.6f seconds\n", time_taken);

    return 0;
}
