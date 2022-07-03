#include "matrix.h"
#include "iostream"

Matrix::Matrix(int r, int c){
    rows = r;
    cols = c;
    entries = (float**) malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; ++i){
        entries[i] = (float*) malloc(cols * sizeof(float));
    }
}


void Matrix::set_val(float v){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            entries[r][c] = v;
        }
    }
};

void Matrix::print(){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            std::cout << entries[r][c] << ' ';
        }
        std::cout << '\n';
    }
}


