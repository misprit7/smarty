#include "matrix.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#define EPSILON 0.001

Matrix::Matrix(){
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int r, int c){
    rows = r;
    cols = c;
    entries = (float**) malloc(rows * sizeof(float*));
    for(int i = 0; i < rows; ++i){
        entries[i] = (float*) std::calloc(cols, sizeof(float));
    }
}

Matrix::Matrix(int r) : Matrix(r, 1) {}

Matrix::Matrix(std::vector<std::vector<float> > vec) : Matrix(vec.size(), vec[0].size()) {
    set_vec(vec);
}

// TODO: Figure out why this isn't necessay and in fact actually and actually
// gives a run time error
// Probably something to do with the way that c++ handles class lifespan that
// I don't understand
//
// I suspect this could cause a memory leak at some point but have yet to see
// any evidence of this
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

void Matrix::apply_inplace(float (*fun)(float)){
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            entries[r][c] = fun(entries[r][c]);
        }
    }
}

Matrix Matrix::apply(float (*fun)(float)){
    Matrix ret(rows, cols);
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            ret[r][c] = fun(entries[r][c]);
        }
    }
    return ret;
}

Matrix Matrix::transpose(){
    Matrix ret(cols, rows);
    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            ret[c][r] = entries[r][c];
        }
    }
    return ret;
}

// TODO: Make this print each character constant width instead to aid ease of
// reading
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

Matrix Matrix::operator*(float x){
    Matrix ret(rows, cols);
    for(int r = 0; r < ret.rows; ++r){
        for(int c = 0; c < ret.cols; ++c){
            ret[r][c] = entries[r][c] * x; 
        }
    }
    return ret;
}

// Might be a way to generalize % and + operators to avoid duplicated code
Matrix Matrix::operator%(const Matrix& mat){
    assert(cols == mat.cols);
    assert(rows == mat.rows);
    Matrix ret(rows, cols);

    for(int r = 0; r < ret.rows; ++r){
        for(int c = 0; c < ret.cols; ++c){
            ret[r][c] = entries[r][c] * mat[r][c];
        }
    }
    return ret;
}

Matrix Matrix::operator+(const Matrix& mat){
    assert(cols == mat.cols);
    assert(rows == mat.rows);
    Matrix ret(rows, cols);

    for(int r = 0; r < ret.rows; ++r){
        for(int c = 0; c < ret.cols; ++c){
            ret[r][c] = entries[r][c] + mat[r][c];
        }
    }
    return ret;
}

bool Matrix::operator==(const Matrix& mat){
    assert(cols == mat.cols);
    assert(rows == mat.rows);

    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            if(std::isnan(entries[r][c]) || std::isnan(mat[r][c]))
                return false;
            // Might want to change this to relative error
            if(std::abs(entries[r][c] - mat[r][c]) > EPSILON)
                return false;
        }
    }
    return true;
}

float* Matrix::operator[](std::size_t i){
    return entries[i];
}

const float* Matrix::operator[](std::size_t i) const {
    return entries[i];
}

