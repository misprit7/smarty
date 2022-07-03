#include <stdio.h>
#include <string.h>
#include <vector>
#include "../src/net.h"


void testNetRun(){
    std::vector<int> layer_len = {2, 3, 2};

    Net net(layer_len);

    std::vector<std::vector<float> > weights0 = 
        {{1, -1}, 
         {-0.5, 2}, 
         {-0.1, 0}};

    std::vector<std::vector<float> > weights1 = 
        {{0.2, 0.1, -0.5}, 
         {-1, 1, 0}};

    net.weights[0].set_vec(weights0);
    net.weights[1].set_vec(weights1);

    net.weights[0].print();
    net.weights[1].print();

    Matrix input(2);
    input.entries[0][0] = 1;
    input.entries[1][0] = 1;

    net.run(input).print();

}

void testMatMul(){
    Matrix mat1(2, 3);
    Matrix mat2(3, 2);
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 3; ++j){
            mat1.entries[i][j] = i+j*2;
            mat2.entries[j][i] = i+j*2;
        }
    }
    mat1.print();
    mat2.print();
    (mat1*mat2).print();
}

int main(void){
    testNetRun();
}

