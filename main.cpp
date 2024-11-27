#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <chrono>
#include <iomanip>
#include "benchmark.h"

int main() {
    int min_size = 16;
    int max_size = 4096;
    int max_threads = 16;

    for (int threads = 1; threads <= max_threads; threads *= 2) {
        std::cout << std::endl;
        std::cout << "Threads: " << threads << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(15) << "Matrix Size" << "|"
                  << std::setw(30) << "Sequential Symmetry Check" << "|"
                  << std::setw(30) << "Implicit Symmmetry Check" << "|"
                  << std::setw(30) << "Explicit Symmetry Check" << "|"
                  << std::setw(30) << "Seqential Transpose" << "|"
                  << std::setw(30) << "Implicit Transpose" << "|"
                  << std::setw(30) << "Explicit Transpose" << "|"
                  << std::endl;

        for (int size = min_size; size <= max_size; size *= 2) {
            BenchmarkOperations(size, threads);
        }
         std::cout << std::endl;
         std::cout << "    ******************************************************************************************************************************************************************************************************" << std::endl;
         std::cout << std::endl;
    }

    return 0;
}