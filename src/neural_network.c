#include "matrix.c"
#include <stdlib.h>

typedef struct NeuralNetwork {
    int layers;
    int *layer_sizes;

    Matrix *biases;
    Matrix *weights;

} NeuralNetwork;

NeuralNetwork create_nn(int layers, int *layer_sizes) {
    NeuralNetwork nn;
    nn.layers = layers;
    nn.layer_sizes = (int*)malloc(sizeof(int) * layers);
    nn.biases = (Matrix*)malloc(sizeof(Matrix) * layers);
    nn.weights = (Matrix*)malloc(sizeof(Matrix) * layers);

    memcpy(nn.layer_sizes, layer_sizes, sizeof(int) * layers);

    // biases and weights start from index 1
    for(int i = 1; i < nn.layers; i++) {
        nn.biases[i] = new_matrix(layer_sizes[i], 1);
        nn.weights[i] = new_matrix(layer_sizes[i], layer_sizes[i-1]);
    }

    return nn;
}

void delete_nn(NeuralNetwork nn) {
    // biases and weights start from index 1
    for(int i = 1; i < nn.layers; i++) {
        delete_matrix(nn.biases[i]);
        delete_matrix(nn.weights[i]);
    }

    free(nn.layer_sizes);
    free(nn.biases);
    free(nn.weights);
}

typedef struct Activations {
    int layers;
    int *layer_sizes;

    Matrix *z;
    Matrix *a;
} Activations;

Activations create_act(int layers, int *layer_sizes) {
    Activations act;
    act.layers = layers;
    act.layer_sizes = (int*)malloc(sizeof(int) * layers);
    act.z = (Matrix*)malloc(sizeof(Matrix) * layers);
    act.a = (Matrix*)malloc(sizeof(Matrix) * layers);

    memcpy(act.layer_sizes, layer_sizes, sizeof(int) * layers);

    // // z starts from index 1
    // for(int i = 0; i < act.layers; i++) {
    //     act.a[i] = new_matrix(layer_sizes[i], 1);
    //     if(i > 0) act.z[i] = new_matrix(layer_sizes[i], 1);
    // }
    return act;
}

void delete_act(Activations act) {
    for(int i = 0; i < act.layers; i++) {
        delete_matrix(act.a[i]);
        delete_matrix(act.z[i]);
    }

    free(act.layer_sizes);
    free(act.a);
    free(act.z);
}

Activations predict(NeuralNetwork nn, Matrix starting_activations) {
    if(starting_activations.rows != nn.layer_sizes[0] || starting_activations.cols != 1) {
        printf("ERROR: starting activations size not compatibile\n");
        exit(1);
    }
    
    Activations res = create_act(nn.layers, nn.layer_sizes);
    res.a[0] = copy_matrix(starting_activations);

    for(int l = 1; l < nn.layers; l++) {
        Matrix p = prod(nn.weights[l], res.a[l-1]);
        res.z[l] = sum(p, nn.biases[l]);

        delete_matrix(p);
        res.a[l] = copy_matrix(res.z[l]);
        matrix_sigmoid(res.a[l]);
    }

    return res;
}

// Computes gradient of the network, used in backprop to adjust weights
// target and activation must be column vectors with length equals to the last layer
NeuralNetwork compute_gradient(NeuralNetwork nn, Matrix target, Activations activation) {
    if(target.rows != nn.layer_sizes[nn.layers - 1] || target.cols != 1) {
        printf("ERROR: target vector not compatible.");
        exit(1);
    }
    if(activation.layers != nn.layers) {
        printf("ERROR: activations not compatible with the network.");
        exit(1);
    }

    NeuralNetwork gradient = create_nn(nn.layers, nn.layer_sizes);
    // TODO: basically everything in this function
}
