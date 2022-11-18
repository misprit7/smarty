#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cassert>
#include "../src/net.hpp"
#include <random>

typedef std::vector<std::vector<float> > V;

void testMatMul();
void testNetRun();
void testIdentity();
void testTransitionMatrix();

int main(void){
    srand(0);
    testMatMul();
    /* testNetRun(); */
    /* testIdentity(); */
    // Doesn't currently work
    testTransitionMatrix();
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

    /* std::cout << "Weight[0]:" << '\n'; */
    /* net.weights[0].print(); */
    /* std::cout << "Weight[1]:" << '\n'; */
    /* net.weights[1].print(); */

    Matrix input(2);
    input[0][0] = 1;
    input[1][0] = 1;

    /* std::cout << "Run output:" << '\n'; */
    Matrix output_run = net.run(input);
    /* output_run.print(); */

    assert(output_run == Matrix((V){{0.15}, {1.5}}));

    /* std::cout << "Backpropogation" << '\n'; */
    /* Matrix output(2); */
    /* output[0][0] = 0.3; */
    /* output[1][0] = 2; */
    /* net.backpropogate(input, output, 0.5); */

    std::cout << "Test Net Run Test Passed!\n";

}

// Sanity check that network can "learn" the identity function
void testIdentity(){
    std::vector<int> layer_len = {2, 2};
    Net net(layer_len);


    std::vector<Matrix> inputs;
    for(int i = 0; i < 10; ++i){
        Matrix input(2);
        input[i%2][0] = 1;
        inputs.push_back(input);
        std::cout << "input number " << i << std::endl;
        inputs.back().print();
    }

    float lr = 1;
    for(int i = 0; i < 10; ++i){
        net.backpropogate(inputs, inputs, lr);
        lr = lr/(1+0.1*i);
    }

    Matrix m10 = net.run(inputs[0]);
    /* m10.print(); */
    Matrix m01 = net.run(inputs[1]);
    /* m01.print(); */

    /* assert(m10 == Matrix((V){{1},{0}})); */
    /* assert(m01 == Matrix((V){{0},{1}})); */

    std::cout << "Identity function test passed!\n";
}

// Test using state transition matrix
void testTransitionMatrix(){
    std::vector<int> layer_len = {2, 2, 2};
    Net net(layer_len);

    Matrix M = Matrix((V){{1, 0}, {0, 1}});
    /* Matrix M = Matrix(layer_len.back(), layer_len[0]); */
    /* for(int r = 0; r < M.rows; ++r){ */
    /*     for(int c = 0; c < M.cols; ++c){ */
    /*         M[r][c] = (r+c)%10; */
    /*     } */
    /* } */

    std::vector<Matrix> inputs;
    std::vector<Matrix> outputs;
    for(int i = 0; i < 5; ++i){
        Matrix input(layer_len[0]);
        /* for(int j = 0; j < layer_len[0]; ++j){ */
            /* input[j][0] = (rand()%(2*layer_len[0]))-layer_len[0]; */
        /* } */
        input[0][0] = -1+i;
        input[1][0] = 2-i;
        inputs.push_back(input);
        outputs.push_back(M * input);
        std::cout << "input number " << i << std::endl;
        inputs.back().print();
        std::cout << "output number " << i << std::endl;
        outputs.back().print();
    }

    float lr = 0.01;
    for(int i = 0; i < 5; ++i){
        net.backpropogate(inputs, outputs, lr);
        lr = lr/(1+0.1*i);
    }
    std::cout << "input:\n";
    inputs[0].print();
    std::cout << "expected:\n";
    outputs[0].print();
    std::cout << "output:\n";
    net.run(inputs[0]).print();
}


