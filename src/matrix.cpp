#include "matrix.h"

Matrix::Matrix(unsigned int r, unsigned int c){
    rows = r;
    cols = c;
    entries = (float**) malloc(rows * sizeof(float*));
    for(unsigned int i = 0; i < rows; ++i){
        entries[i] = (float*) malloc(cols * sizeof(float));
    }
}
