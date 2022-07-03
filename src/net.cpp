#include "net.h"

Net::Net(std::vector<int> layers){
    num_layers = layers.size();
    layer_len = layers;
    for(unsigned int i = 0; i < num_layers - 1; ++i){
        Matrix t(layer_len[i+1], layer_len[i]);
        t.set_val(1.);
        weights.push_back(t);
    }
}

