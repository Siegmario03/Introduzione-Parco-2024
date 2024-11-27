#include "sequential.h"
#include <cmath>

bool checkSym(const unoptimized_matrix& matrix) {
    float eps = 1e-6;   
    bool symmetric = true;
    int n = matrix.size_;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float difference = std::fabs(matrix.data_[i * n + j] - matrix.data_[j * n + i]);
            if (difference > eps) {
                symmetric = false;
            }
        }
    }
    
    return symmetric;
}

void matTranspose(const unoptimized_matrix& matrix_1, unoptimized_matrix& matrix_2) {
    
    for (int i = 0; i < matrix_1.size_; ++i) {
        for (int j = 0; j < matrix_1.size_; ++j) {
            matrix_2.data_[j * matrix_1.size_ + i] = matrix_1.data_[i * matrix_1.size_ + j];
        }
    }
}