#include <stdio.h>

char *characters = " .-/#";

void print_image(int rows, int cols, float *data) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            float value = data[i * cols + j];
            printf("%c", characters[(int)(value / 0.2)]);
        }
        printf("\n");
    }
}
