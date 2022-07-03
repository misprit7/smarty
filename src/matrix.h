#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
    public: 

        unsigned int rows, cols;
        float **entries;

        Matrix(unsigned int r, unsigned int c);
};

#endif
