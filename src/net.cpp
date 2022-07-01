
#include <vector>

class Net 
{ 
    public: 


    // Number of layers, including input and output
    unsigned int num_layers;
    // List of layer lengths
    std::vector<int> layer_len;
    // List of matrices of weights
    float ***weights;

    Net(std::vector<int> layer_len, float ***weights){
        num_layers = layer_len.size();
        

    }

};

