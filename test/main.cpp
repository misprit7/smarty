#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cassert>
#include "../src/net.h"

void testMatMul();
void testNetRun();
void testIdentity();

int main(void){
    testMatMul();
}

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

    std::cout << "Weight[0]:" << '\n';
    net.weights[0].print();
    std::cout << "Weight[1]:" << '\n';
    net.weights[1].print();

    Matrix input(2);
    input[0][0] = 1;
    input[1][0] = 1;

    std::cout << "Run output:" << '\n';
    Matrix output_run = net.run(input);
    output_run.print();

    std::cout << "Backpropogation" << '\n';
    Matrix output(2);
    output[0][0] = 0.3;
    output[1][0] = 2;
    net.backpropogate(input, output, 0.5);

}

// Sanity check that network can "learn" the identity function
void testIdentity(){
    std::vector<int> layer_len = {2, 2};
    Net net(layer_len);

    auto out_fun = [](Matrix &in) -> Matrix& {
        return in;
    };

    std::vector<Matrix> inputs;
    for(int i = 0; i < 1000; ++i){
        Matrix input(2);
        input[i%2][0] = 1;
        inputs.push_back(input);
    }

    float lr = 1;
    for(int i = 0; i < inputs.size(); ++i){
        net.backpropogate(inputs[i], out_fun(inputs[i]), lr);
        lr = lr/(1+0.1*i);
    }

    Matrix m10 = net.run(inputs[0]);
    m10.print();
    Matrix m01 = net.run(inputs[1]);
    m01.print();

}

void testMatMul(){
    Matrix mat1(2, 3);
    Matrix mat2(3, 2);
    Matrix out(2, 2);
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 3; ++j){
            mat1[i][j] = i+j*2;
            mat2[j][i] = i+j*2;
        }
    }
    out.set_vec({{20, 26}, {26, 35}});
    assert(out == mat1*mat2);
    std::cout << "Matrix Multiply Test Passed!\n";
}


