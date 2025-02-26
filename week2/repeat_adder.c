#include <stdio.h>

int main() {
    int in_arg = 2;
    int multiple = 3;
    int output = 0;
    for (int i = 0; i < in_arg; i++) {
        output = output + multiple;
    }
    printf("%d\n", output);
    return 0;
}
