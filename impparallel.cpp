#include <vector>
#include <cmath>
#include "impparallel.h"


bool checkSymimp(const optimized_matrix& mat) {
    int size = mat.size;
    int block_size = mat.block_size;
    int blocks_per_row = size / block_size;
    bool symmetric = true;

    for (int i = 0; i < blocks_per_row; ++i) {
        for (int j = i; j < blocks_per_row; ++j) {
            for (int bi = 0; bi < block_size; ++bi) {
                for (int bj = 0; bj < block_size; ++bj) {
                    if (mat.data[mat.index(i * block_size + bi, j * block_size + bj)] !=
                        mat.data[mat.index(j * block_size + bj, i * block_size + bi)]) {
                        symmetric = false;
                    }
                }
            }
        }
    }

    return symmetric;
}

void matTransposeimp(const optimized_matrix& mat, optimized_matrix& transposed) {
    int size = mat.size;
    int block_size = mat.block_size;
    int blocks_per_row = size / block_size;

    for (int block_row = 0; block_row < blocks_per_row; ++block_row) {
        for (int block_col = 0; block_col < blocks_per_row; ++block_col) {
            for (int inner_row = 0; inner_row < block_size; ++inner_row) {
                for (int inner_col = 0; inner_col < block_size; ++inner_col) {
                    int src_row = block_row * block_size + inner_row;
                    int src_col = block_col * block_size + inner_col;
                    int dst_row = block_col * block_size + inner_col;
                    int dst_col = block_row * block_size + inner_row;

                    transposed.data[transposed.index(dst_row, dst_col)] = mat.data[mat.index(src_row, src_col)];
                    
                }
            }
        }
    }
}
