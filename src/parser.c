#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct MNIST_dataset {
    int images;
    int rows;
    int cols;
    float *data;
} MNIST_dataset;

typedef struct MNIST_labels {
    int images;
    int *data;
} MNIST_labels;

// define functions to read integers and convert to little endian
void fread_little_endian(unsigned int *buffer, unsigned int size, unsigned int n, FILE *f) {
    unsigned char *bytes = (unsigned char*)malloc(n * size);

    fread(bytes, 1, size*n, f);

    for(int i=0; i<n; i++) {
        buffer[i] = (bytes[4*i] << 24) | (bytes[4*i + 1] << 16) | (bytes[4*i + 2] << 8) | (bytes[4*i + 3]); 
    }
}

float normalize(unsigned char pixel) {
    return (float)pixel / 256.0;
}

MNIST_dataset retrieve_images(FILE* fp) {
    /*  
        IDX file format:
        4 bytes: magic number (byte 3 is type of data, bu)
        then (size) lines of 4 bytes each containg sizes in each dimension
        then the raw data
    
        byte order is big endian while my cpu reads in little endian 
    */

    int magic; 
    fread_little_endian(&magic, sizeof(int), 1, fp);

    int dimensions = magic & 255;
    int data_type = (magic >> 8) & 255;
    printf("magic: %04x\n", magic);
    printf("number of dimensions: %d, data_type code: %d\n", dimensions, data_type);

    assert(dimensions == 3 && data_type == 8);

    int sizes[3];
    fread_little_endian(sizes, sizeof(int), 3, fp);
    
    printf("sizes: %d %d %d\n", sizes[0], sizes[1], sizes[2]);

    MNIST_dataset dataset;
    dataset.images = sizes[0];
    dataset.rows = sizes[1];
    dataset.cols = sizes[2];

    size_t data_size = dataset.images * dataset.rows * dataset.cols;
    dataset.data = (float *)malloc(sizeof(float) * data_size);

    for(int i = 0; i < dataset.images; i++) {
        for(int r = 0; r < dataset.rows; r++) {
            for(int c = 0; c < dataset.cols; c++) {
                unsigned char pixel;
                fread(&pixel, sizeof(char), 1, fp);

                // normalize and store in data
                int image_size = dataset.rows * dataset.cols;
                dataset.data[i*image_size + r*dataset.cols + c] = normalize(pixel);
            }
        }
    }

    return dataset;
}

MNIST_labels retrieve_labels(FILE* fp) {
    int magic; 
    fread_little_endian(&magic, sizeof(int), 1, fp);

    int dimensions = magic & 255;
    int data_type = (magic >> 8) & 255;
    printf("magic: %04x\n", magic);
    printf("number of dimensions: %d, data_type code: %d\n", dimensions, data_type);

    assert(dimensions == 1 && data_type == 8);

    int size;
    fread_little_endian(&size, sizeof(int), 1, fp);

    MNIST_labels labels;
    labels.images = size;
    labels.data = (int *)malloc(sizeof(int) * labels.images);
        
    for(int i = 0; i < labels.images; i++) {
        char label;

        fread(&label, sizeof(char), 1, fp);
        labels.data[i] = label;
    }

    return labels;
}
