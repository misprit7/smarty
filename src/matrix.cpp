#include "matrix.h"
#include <iostream>
#include <cassert>
#include <vector>

Matrix::Matrix(int r, int c){
    rows = r;
    cols = c;
    entries = (float**) malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; ++i){
        entries[i] = (float*) malloc(cols * sizeof(float));
    }
}

Matrix::Matrix(int r) : Matrix(r, 1) {}

Matrix::~Matrix(){
    /* for(int i = 0; i < rows; ++i){ */
    /*     free(entries[i]); */
    /* } */
    /* free(entries); */
}

void Matrix::set_val(float v){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            entries[r][c] = v;
        }
    }
}

void Matrix::set_vec(std::vector<std::vector<float> > vec){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            entries[r][c] = vec[r][c];
        }
    }
}

void Matrix::apply(float (*fun)(float)){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            entries[r][c] = fun(entries[r][c]);
        }
    }
}

void Matrix::print(){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            std::cout << entries[r][c] << ' ';
        }
        std::cout << '\n';
    }
}


// Relatively bad O(n^3) implementation for now
Matrix Matrix::operator*(const Matrix& mat){
    assert(cols == mat.rows);
    Matrix ret(rows, mat.cols);

    for(int r = 0; r < ret.rows; ++r){
        for(int c = 0; c < ret.cols; ++c){
            ret.entries[r][c] = 0;
            for(int i = 0; i < cols; ++i){
                ret.entries[r][c] += entries[r][i] * mat.entries[i][c];
            }
        }
    }
    return ret;
}

