#include "net.h"
#include <vector>

Net::Net(std::vector<int> layer_sizes){
    num_layers = layer_sizes.size();
    layer_len = layer_sizes;
    for(unsigned int i = 0; i < num_layers - 1; ++i){
        Matrix t(layer_len[i+1], layer_len[i]);
        t.set_val(1.);
        weights.push_back(t);
    }
}


Matrix Net::run(Matrix input){
    // Don't really have to keep track of intermediate layers
    std::vector<Matrix> layers;
    layers.push_back(input);
    int i = 0;
    while(layers.size() < num_layers){
        layers.push_back(layers.back() * weights[i++]);
    }
    return layers.back();
}
