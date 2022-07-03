#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
    public: 

         int rows, cols;
        float **entries;

        Matrix( int r,  int c);

        void set_val(float v);
        void print();
};

#endif
