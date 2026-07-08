#include "sigmoid.c"
#include <string.h>
#include <stdlib.h>

typedef struct Matrix {
    int rows;
    int cols;
    float *data;
} Matrix;

Matrix new_matrix(int rows, int cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    A.data = (float *)malloc(sizeof(float) * A.rows * A.cols);

    // fill data with random numbers from 0 to 1 (might make a separate function later)
    for(int i=0; i<A.rows * A.cols; i++) {
        A.data[i] = ((float)rand() / RAND_MAX) * 2.0 - 1.0;
    }

    return A;
}

void delete_matrix(Matrix A) {
    free(A.data);
}

Matrix copy_matrix(Matrix A) {
    Matrix B = new_matrix(A.rows, A.cols);
    memcpy(B.data, A.data, sizeof(float) * A.rows * A.cols);

    return B;
}

Matrix prod(Matrix A, Matrix B) {
    if(A.cols != B.rows) {
        printf("ERROR: matrix dimensions not compatible\n");
        exit(1);
    }

    Matrix C = new_matrix(A.rows, B.cols);

    for(int i = 0; i < C.rows; i++) {
        for(int j = 0; j < C.cols; j++) {
            C.data[i * C.cols + j] = 0;
            for(int k = 0; k < A.cols; k++) {
                C.data[i * C.cols + j] += A.data[i * A.cols + k] * B.data[k * B.cols + j];
            }
        }
    }

    return C;
}

Matrix sum(Matrix A, Matrix B) {
    if(A.rows != B.rows || A.cols != B.cols) {
        printf("ERROR: matrix dimensions not compatible\n");
        exit(1);
    }

    Matrix C = new_matrix(A.rows, A.cols);
    for(int i = 0; i < C.rows; i++) {
        for(int j = 0; j < C.cols; j++) {
            C.data[i * C.cols + j] = A.data[i * A.cols + j] + B.data[i * B.cols + j];
        }
    }

    return C;
}

// applies sigmoid to each element in A
void matrix_sigmoid(Matrix A) {
    for(int i = 0; i < A.rows * A.cols; i++) {
        A.data[i] = sigmoid(A.data[i]);
    }
} 
