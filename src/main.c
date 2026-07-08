#include <stdio.h>
#include "print.c"
#include "parser.c"
#include "neural_network.c"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "usage: ./main images.idx labels.idx\n");
        exit(0);
    }

    char *images_path = argv[1];
    char *labels_path = argv[2];

    FILE *fp_images = fopen(images_path, "rb"); 
    FILE *fp_labels = fopen(labels_path, "rb"); 

    if(!fp_images || !fp_labels) {
        fprintf(stderr, "file doesn't exist\n");
        exit(0);
    }

    MNIST_dataset dataset = retrieve_images(fp_images);
    MNIST_labels labels = retrieve_labels(fp_labels);

    int layers = 4;
    int layer_sizes[4] = {dataset.cols * dataset.rows, 16, 16, 10};

    NeuralNetwork nn = create_nn(layers, layer_sizes);

    int pixels = dataset.rows * dataset.cols;
    for(int i = 0; i < 10; i++) {
        printf("label: %d\n", labels.data[i]);
        // print_image(dataset.rows, dataset.cols, dataset.data + i * pixels);
        printf("prediction: ");
        Matrix activations = new_matrix(pixels, 1);
        memcpy(activations.data, dataset.data + i * pixels, sizeof(float) * pixels);

        Activations act = predict(nn, activations);
        for(int i=0; i<10; i++) {
            printf("%.2f ", act.a[act.layers-1].data[i]);
        }
        printf("\n");

        delete_matrix(activations);
    }  
    
    delete_nn(nn);
    free(dataset.data);
    free(labels.data);
}
