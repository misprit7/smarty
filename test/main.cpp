#include <stdio.h>
#include <string.h>
#include <vector>
#include "../src/net.h"

int main(void){

    std::vector<int> layer_len = {2, 3, 2};

    Net net(layer_len);

    net.weights[1].print();
}
