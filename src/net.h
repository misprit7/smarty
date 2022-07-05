#ifndef NET_H
#define NET_H

#include <vector>
#include "matrix.h"

class Net 
{ 
    // I'm being pretty loose with private vs. public for now since it makes 
    // debugging a lot easier
    public: 
        // Number of layers, including input and output, should be >=2
        unsigned int num_layers;
        // List of layer lengths
        std::vector<int> layer_len;
        // List of matrices of weights
        // Should have length num_layers-1
        std::vector<Matrix> weights;

        // Activation function
        float (*act)(float);
        // Cost function
        float (*cost)(Matrix &y1, Matrix &y2);

        // Derivatives for input functions
        // These could have been computed numerically but might as well
        // compute directly if it's easy
        // Activation function
        float (*act_d)(float);
        // Cost function
        Matrix (*cost_d)(Matrix &y1, Matrix &y2);

        Net(std::vector<int> layer_sizes);

        // Runs the neural network
        // Matrix must be a layer_len[0] * 1 matrix
        // Output is layer_len[-1] * 1 matrix
        Matrix run(Matrix &input);

        // Updates weight from input matrices
        // lr: learning rate
        void backpropogate(Matrix &input, Matrix &output, float lr);
};

#endif
