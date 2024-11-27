#ifndef UNOPTIMIZEDMATRIX_H
#define UNOPTIMIZEDMATRIX_H

#include <vector>
#include <cstdlib>
#include <ctime>

class unoptimized_matrix {
public:
    int size_;
    std::vector<float> data_;

    unoptimized_matrix(int size) : size_(size), data_(size * size) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        #pragma omp parallel for
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                data_[i * size_ + j] = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            }
        }
    }
};

#endif