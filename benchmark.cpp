#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>
#include <iomanip>
#include <functional>
#include "benchmark.h"
#include "parallel.h"
#include "sequential.h"
#include "impparallel.h"
#include "optimizedmatrix.h"
#include "unoptimizedmatrix.h"

void BenchmarkOperations(int matrix_size, int num_threads) {
    int num_repeats = 250;
    omp_set_num_threads(num_threads);

    unoptimized_matrix matrix_A(matrix_size);
    unoptimized_matrix matrix_B(matrix_size);

    optimized_matrix opt_matrix_A(matrix_size, 16);
    optimized_matrix opt_matrix_B(matrix_size, 16);

    bool symmetric;

    auto computeAverage = [&](std::function<void()> func) {
        double total_time = 0.0;
        for (int i = 0; i < num_repeats; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            (void)func();
            auto end = std::chrono::high_resolution_clock::now();
            total_time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
        return total_time / num_repeats;
    };

    double avg_symcheck = computeAverage([&]() { symmetric = checkSym(matrix_A); });
    double avg_symcheck_imparallel = computeAverage([&]() { symmetric = checkSymimp(opt_matrix_A); });
    double avg_symcheck_exparallel = computeAverage([&]() { symmetric = checkSymOMP(opt_matrix_A); });
    double avg_transp = computeAverage([&]() { matTranspose(matrix_A, matrix_B); });
    double avg_transp_imparallel = computeAverage([&]() { matTransposeimp(opt_matrix_A, opt_matrix_B); });
    double avg_transp_exparallel = computeAverage([&]() { matTransposeOMP(opt_matrix_A, opt_matrix_B); });

    std::cout << std::setw(15) << matrix_size
              << std::setw(30) << avg_symcheck
              << std::setw(30) << avg_symcheck_imparallel
              << std::setw(30) << avg_symcheck_exparallel
              << std::setw(30) << avg_transp
              << std::setw(30) << avg_transp_imparallel 
              << std::setw(30) << avg_transp_exparallel 
              << std::endl;
}