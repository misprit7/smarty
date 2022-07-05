#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

// Maybe template in future? 
//
// TODO: Add support for more efficient column vectors and transposes instead
// of the current Nx1 vectors and deep copy transposes which have unnecessary
// memory footprints
class Matrix {
    private:
        float **entries;

    public: 

        int rows, cols;

        Matrix();

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
        void apply_inplace(float (*fun)(float));
        Matrix apply(float (*fun)(float));

        Matrix transpose();

        // Prints matrix to screen
        void print();

        // * operator is matrix multiplication
        Matrix operator*(const Matrix& mat);
        // * operator is also scalar multiplication
        Matrix operator*(float x);
        // % operator is Hammard product
        Matrix operator%(const Matrix& mat);
        // + operator is elementwise addition
        Matrix operator+(const Matrix& mat);
        // TODO: Implement subtraction as negative of addition
        // == is actual matrix equality
        // To even compare the matrices should be the same cols/rows
        // i.e. assertion fail if they don't
        bool operator==(const Matrix& mat);

        // Array subscripting
        float* operator[](std::size_t i);
        const float* operator[](std::size_t i) const;
};

#endif
