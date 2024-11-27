#include "parallel.h"
#include <omp.h>
#include <cmath>

bool checkSymOMP(const optimized_matrix& mat) {
    float epsilon = 1e-6;

    int size = mat.size;
    int block_size = mat.block_size;
    int blocks_per_row = (size + block_size - 1) / block_size;

    bool symmetric = true;

    #pragma omp parallel for shared(symmetric) schedule(dynamic)
    for (int block_row = 0; block_row < blocks_per_row; ++block_row) {
        for (int block_col = block_row; block_col < blocks_per_row; ++block_col) {
            int start_row = block_row * block_size;
            int start_col = block_col * block_size;

            for (int i = 0; i < block_size; ++i) {
            
                #pragma omp simd
                for (int j = 0; j < block_size; ++j) {
                    int global_row = start_row + i;
                    int global_col = start_col + j;

                    if (global_row >= size || global_col >= size) continue;

                    float val1 = mat.data[mat.index(global_row, global_col)];
                    float val2 = mat.data[mat.index(global_col, global_row)];

                    if (std::fabs(val1 - val2) > epsilon) {
                    
                        symmetric = false;
                    }
                }
            }
        }
    }

    return symmetric;
}

void matTransposeOMP(const optimized_matrix& mat, optimized_matrix& transposed) {

    int size = mat.size;
    int block_size = mat.block_size;

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int block_row = 0; block_row < size; block_row += block_size) {
        for (int block_col = 0; block_col < size; block_col += block_size) {
            for (int i = 0; i < block_size; ++i) {
            
                for (int j = 0; j < block_size; j += 4) {
                    int global_row = block_row + i;
                    int global_col1 = block_col + j;
                    int global_col2 = block_col + j + 1;
                    int global_col3 = block_col + j + 2;
                    int global_col4 = block_col + j + 3;
                    
                    if (global_row >= size || global_col1 >= size) continue;


                    transposed.data[transposed.index(global_col1, global_row)] =
                        mat.data[mat.index(global_row, global_col1)];

                    if (global_col2 < size) {
                        transposed.data[transposed.index(global_col2, global_row)] =
                            mat.data[mat.index(global_row, global_col2)];
                    }

                    if (global_col3 < size) {
                        transposed.data[transposed.index(global_col3, global_row)] =
                            mat.data[mat.index(global_row, global_col3)];
                    }

                    if (global_col4 < size) {
                        transposed.data[transposed.index(global_col4, global_row)] =
                            mat.data[mat.index(global_row, global_col4)];
                    }
                }
            }
        }
    }
}