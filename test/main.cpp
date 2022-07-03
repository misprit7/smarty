#include <stdio.h>
#include <string.h>
#include <vector>
#include "../src/net.h"

int main(void){

    std::vector<int> layer_len = {2, 3, 2};

    Net net(layer_len);

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


