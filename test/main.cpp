#include <stdio.h>
#include <string.h>
#include <vector>
#include "../src/net.h"

int main(void){

    std::vector<int> layer_len = {2, 3, 2};
    float **weights[layer_len.size()-1];
    /* for(int i = 0; i < layer_len.size()-1; ++i){ */
    /*     weights[i] = (float**)malloc(layer_len[i+1] * sizeof(weights[0][0])); */
    /*     for(int j = 0; j < layer_len[i+1]; ++j){ */
    /*         weights[i][j] = (float*)malloc(layer_len[i] * sizeof(weights[0][0][0])); */
    /*     } */
    /* } */

    Net * net = new Net(layer_len, weights);

    printf("Hello world\n");
}
