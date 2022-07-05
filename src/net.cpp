#include "net.h"
#include <vector>
#include <cassert>

static float relu(float x){
    return x < 0 ? 0 : x;
}

// Arbitrarily choose derivative at zero to be 1
static float relu_d(float x){
    return x < 0 ? 0 : 1;
}

static float sum_of_squares(Matrix &y1, Matrix &y2){
    assert(y1.rows == y2.rows && y1.cols == y2.cols);
    assert(y1.cols == 1);

    float sum = 0;
    for(int i = 0; i < y1.rows; ++i){
        sum += (y1[i][0] - y2[i][0]) * (y1[i][0] - y2[i][0]);
    }
    return sum;
}

static Matrix sum_of_squares_d(Matrix &y1, Matrix &y2){
    assert(y1.rows == y2.rows && y1.cols == y2.cols);
    assert(y1.cols == 1);

    Matrix ret(y1.rows, y1.cols);

    for(int i = 0; i < y1.rows; ++i){
        // d/dx (x-a)^2 = 2(x-a)
        ret[i][0] = 2 * (y1[i][0] - y2[i][0]);
    }
    return ret;
}

Net::Net(std::vector<int> layer_sizes){
    num_layers = layer_sizes.size();
    layer_len = layer_sizes;
    // Default to relu for now
    // Can make this a parameter or something later
    act = relu;
    act_d = relu_d;
    // Make sum of squares default cost function
    cost = sum_of_squares;
    cost_d = sum_of_squares_d;
    for(unsigned int i = 0; i < num_layers - 1; ++i){
        Matrix t(layer_len[i+1], layer_len[i]);
        t.set_val(1.);
        weights.push_back(t);
    }
}


Matrix Net::run(Matrix &input){
    // Don't really have to keep track of intermediate layers, but doing it now
    // for debugging
    std::vector<Matrix> layers;
    layers.push_back(input);
    int i = 0;
    while(layers.size() < num_layers){
        layers.push_back(weights[i++] * layers.back());
        layers.back().apply_inplace(act);
    }
    return layers.back();
}

// Implementation based on this: 
// https://en.wikipedia.org/wiki/Backpropagation
//
// Variable conventions follow that, so reference wikipedia for definitions
void Net::backpropogate(Matrix &input, Matrix &output){
    std::vector<Matrix> a;
    std::vector<Matrix> f_prime;
    
    // Run through net forward to calculate intermediate parameters
    a.push_back(input);
    int i = 0;
    while(a.size() < num_layers){
        a.push_back(weights[i++] * a.back());
        // right now a.back() is z
        f_prime.push_back(a.back().apply(act_d));

        a.back().apply_inplace(act);
    }

    Matrix grad_a_C = cost_d(a.back(), output);

    // Calculate deltas + gradients
    std::vector<Matrix> delta(num_layers);
    // index zero is never used, but nicer for indexing this way
    std::vector<Matrix> grad_w_C(num_layers);

    // Hammard product
    delta.back() = f_prime.back() % grad_a_C;
    for(int l = num_layers-1; l > 0; --l){
        grad_w_C[l] = delta[l] * a[l-1].transpose();
        delta[l-1] = f_prime[l-1] % (weights[l-1].transpose() * delta[l]);
    }

}


