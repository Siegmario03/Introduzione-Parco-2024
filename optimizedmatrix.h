#ifndef OPTIMIZEDMATRIX_H
#define OPTIMIZEDMATRIX_H

#include <vector>
#include <cstdlib>
#include <ctime>

class optimized_matrix {
public:
    int size;
    int block_size;
    std::vector<float> data;

    optimized_matrix(int size, int block_size) : size(size), block_size(block_size), data(size * size) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                data[index(i, j)] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            }
        }
    }

    int index(int row, int col) const {
        int blocks_per_row = size / block_size;
        int block_row = row / block_size;
        int block_col = col / block_size;

        int block_start = (block_row * blocks_per_row + block_col) * block_size * block_size;

        int inner_row = row % block_size;         
        int inner_col = col % block_size;

        return block_start + inner_row * block_size + inner_col;
    }
};

#endif