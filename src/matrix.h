#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

// Maybe template in future? 
class Matrix {
    public: 

        int rows, cols;
        float **entries;

        // r: rows, c: cols
        Matrix(int r,  int c);
        // r: rows, c: 1
        Matrix(int r);

        // frees dynamically allocated entries
        ~Matrix();

        // Sets all values to v
        void set_val(float v);
        // Sets values to specified vec
        void set_vec(std::vector<std::vector<float> > vec);
        // Applies given function to each element
        void apply(float (*fun)(float));

        // Prints matrix to screen
        void print();

        Matrix operator*(const Matrix& mat);
};

#endif
