#ifndef MATRIX_H
#define MATRIX_H

#include <string>

// Maybe template in future? 
class Matrix {
    public: 

        int rows, cols;
        float **entries;

        // r: rows, c: cols
        Matrix( int r,  int c);
        // r: rows, c: 1
        Matrix( int r);

        // Sets all values to v
        void set_val(float v);
        // Prints matrix to screen
        void print();

        Matrix operator*(const Matrix& mat);
};

#endif
