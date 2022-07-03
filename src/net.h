#ifndef NET_H
#define NET_H

#include <vector>
#include "matrix.h"

class Net 
{ 
    public: 
        // Number of layers, including input and output, should be >=2
        unsigned int num_layers;
        // List of layer lengths
        std::vector<int> layer_len;
        // List of matrices of weights
        std::vector<Matrix> weights;

        Net(std::vector<int> layer_sizes);

        // Runs the neural network
        // Matrix must be a layer_len[0] * 1 matrix
        // Output is layer_len[-1] * 1 matrix
        Matrix run(Matrix input);
};

#endif
