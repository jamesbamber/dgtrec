#include "matrix.c"

typedef struct NeuralNetwork {
    int layers;
    int *layer_sizes;

    Matrix *biases;
    Matrix *weights;

} NeuralNetwork;

NeuralNetwork create_nn(int layers, int *layer_sizes) {
    NeuralNetwork nn;
    nn.layers = layers;
    nn.layer_sizes = layer_sizes;
    nn.biases = (Matrix*)malloc(sizeof(Matrix) * layers);
    nn.weights = (Matrix*)malloc(sizeof(Matrix) * layers);

    for(int i=0; i<nn.layers; i++) {
        nn.biases[i] = new_matrix(layer_sizes[i], 1);
    }

    for(int i=0; i<nn.layers-1; i++) {
        nn.weights[i] = new_matrix(layer_sizes[i+1], layer_sizes[i]);
    }
}
