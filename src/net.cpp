#include "net.hpp"
#include <iostream>
#include <ostream>
#include <vector>
#include <cassert>

static float relu(float x){
    return x < 0 ? 0 : x;
}

// Arbitrarily choose derivative at zero to be 1
static float relu_d(float x){
    return x < 0 ? 0 : 1;
}

static float linear(float x){
    return x;
}

static float linear_d(float x){
    return 1;
}

static float sum_of_squares(Matrix &y1, Matrix &y2){
    assert(y1.rows == y2.rows && y1.cols == y2.cols);
    assert(y1.cols == 1);

    float sum = 0;
    for(int i = 0; i < y1.rows; ++i){
        sum += (y1[i][0] - y2[i][0]) * (y1[i][0] - y2[i][0]);
    }
    return sum / 2.0;
}

static Matrix sum_of_squares_d(Matrix &y1, Matrix &y2){
    assert(y1.rows == y2.rows && y1.cols == y2.cols);
    assert(y1.cols == 1);

    Matrix ret(y1.rows, y1.cols);

    for(int i = 0; i < y1.rows; ++i){
        // d/dx (x-a)^2 = 2(x-a)
        ret[i][0] = (y1[i][0] - y2[i][0]);
    }
    return ret;
}

Net::Net(std::vector<int> layer_sizes){
    num_layers = layer_sizes.size();
    layer_len = layer_sizes;
    // Default to relu for now
    // Can make this a parameter or something later
    /* act = relu; */
    /* act_d = relu_d; */
    act = linear;
    act_d = linear_d;
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

#if 0
std::vector<Matrix> Net::Gradient(Matrix &input, Matrix &output){
    std::vector<Matrix> a; // Length: num_layers
    std::vector<Matrix> f_prime; // Length: num_layers - 1
    
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
    // index = l-1
    std::vector<Matrix> delta(num_layers-1);
    std::vector<Matrix> grad_w_C(num_layers-1);

    // Hammard product
    delta.back() = f_prime.back() % grad_a_C;
    grad_w_C.back() = delta.back() * a[num_layers-2].transpose();
    grad_w_C.back().print();
    std::cout << std::endl;
    // This is quite confusing since wikipedia is 1 indexed and c++ is 0
    // indexed
    for(int l = num_layers-2; l > 0; --l){
        delta[l-1] = f_prime[l-1] % (weights[l].transpose() * delta[l]);
        // This looks different than wikipedia because grad_w_C and delta
        // have one less element than a
        grad_w_C[l-1] = delta[l-1] * a[l-1].transpose();
        grad_w_C[l-1].print();
        std::cout << std::endl;
    }
    return grad_w_C;
}
#endif

std::vector<Matrix> Net::Gradient(Matrix &input, Matrix &output){
    if(num_layers <= 2) return {};
    std::vector<Matrix> a;
    std::vector<Matrix> o;
    std::vector<Matrix> g_prime;
    std::vector<Matrix> delta(num_layers-1);
    std::vector<Matrix> gradients(num_layers-1);
    
    // Run through net forward to calculate intermediate parameters
    a.push_back(input);
    o.push_back(input);
    int i = 0;
    while(a.size() < num_layers){
        a.push_back(weights[i++] * o.back());
        g_prime.push_back(a.back().apply(act_d));
        o.back() = a.back().apply(act);
    }

    int k = num_layers-2;
    delta[k] = g_prime[k] % cost_d(a.back(), output);
    gradients[k] = o[k] * delta[k].transpose();

    for(--k; k >= 0; --k){
        delta[k] = g_prime[k] % (weights[k+1] * delta[k+1]);
        gradients[k] = o[k] * delta[k].transpose();
    }
    return gradients;
}

// Implementation based on this: 
// https://en.wikipedia.org/wiki/Backpropagation
// https://en.wikipedia.org/wiki/Stochastic_gradient_descent
// Variable conventions follow that, so reference wikipedia for definitions
void Net::backpropogate(std::vector<Matrix>& input, std::vector<Matrix>& output, float lr){
    std::vector<std::vector<Matrix>> grads;
    for(int i = 0; i < input.size(); ++i){
        std::cout << "grads " << i << ":\n";
        grads.push_back(Gradient(input[i], output[i]));
    }
    // Calculate average of all gradients
    // Sloppy without a copy constructor but whatever
    std::vector<Matrix> grad = grads[0];
    for(auto g : grads){
        for(int i = 0; i < g.size(); ++i){
            grad[i] = grad[i] + g[i];
        }
    }
    for(int i = 0; i < weights.size(); ++i){
        grad[i] = grad[i] * (1.0/grads.size());
        std::cout << "grad:\n";
        grad[i].print();
        weights[i] = weights[i] + grad[i] * (-lr);
        std::cout << "weights:\n";
        weights[i].print();

    }
}


