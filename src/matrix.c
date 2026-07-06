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

    return A;
}

void delete_matrix(Matrix A) {
    free(A.data);
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
