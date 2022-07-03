#ifndef NET_H
#define NET_H

#include <vector>


class Net 
{ 
    public: 


    // Number of layers, including input and output
    unsigned int num_layers;
    // List of layer lengths
    std::vector<int> layer_len;
    // List of matrices of weights

    Net(std::vector<int> layer_len, float ***weights);
};

#endif
