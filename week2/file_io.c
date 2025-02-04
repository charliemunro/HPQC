#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[255];

    // Writing to a file
    fp = fopen("example.txt", "w");
    if(fp == NULL) {
        perror("Error opening file");
        return(-1);
    }
    fprintf(fp, "Hello, world!\n");
    fclose(fp);

    // Reading from a file
    fp = fopen("example.txt", "r");
    if(fp == NULL) {
        perror("Error opening file");
        return(-1);
    }
    fgets(buffer, 255, fp);
    printf("File content: %s", buffer);
    fclose(fp);

    return 0;
}

