#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/matrix.c"

void test_sum() {
    Matrix a = new_matrix(2, 3), b = new_matrix(2, 3);

    for(int i=0; i<6; i++) {
        a.data[i] = i;
        b.data[i] = (float)i / 2;
    }

    Matrix c = sum(a, b);

    assert(c.rows == 2 && c.cols == 3);

    for(int i=0; i<6; i++) {
        assert(c.data[i] == (i + (float)i/2));
    }

    delete_matrix(a);
    delete_matrix(b);
    delete_matrix(c);
}

void test_prod() {
    Matrix a = new_matrix(2, 3), b = new_matrix(3, 2);

    for(int i=0; i<6; i++) {
        a.data[i] = i+1;
        b.data[i] = i+1;
    }

    Matrix c = prod(a, b);

    assert(c.rows == 2 && c.cols == 2);

    assert(
        c.data[0] == 22.0 &&
        c.data[1] == 28.0 &&
        c.data[2] == 49.0 &&
        c.data[3] == 64.0
    );

    delete_matrix(a);
    delete_matrix(b);
    delete_matrix(c);
}

void test_sigmoid() {
    Matrix A = new_matrix(3, 3);
    for(int i = 0; i < A.rows * A.cols; i++) {
        assert(-1 <= A.data[i] && A.data[i] <= 1);
        A.data[i] = A.data[i] * 2 - 1;
    }
    
    for(int t=0; t<3; t++) {
        matrix_sigmoid(A);
        for(int i = 0; i < A.rows * A.cols; i++) {
            assert(0 <= A.data[i] && A.data[i] <= 1);
            A.data[i] *= 5;
        }
    }

    delete_matrix(A);
}

int main() {
    printf("Testing matrix sum: ");
    test_sum();
    printf("OK\n");

    printf("Testing matrix product: ");
    test_prod();
    printf("OK\n");

    printf("Testing sigmoid function: ");
    test_sigmoid();
    printf("OK\n");
}
