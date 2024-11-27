#ifndef PARALLEL_H
#define PARALLEL_H

#include "optimizedmatrix.h"

bool checkSymOMP(const optimized_matrix& matrix);
void matTransposeOMP(const optimized_matrix& matrix_1, optimized_matrix& matrix_2);

#endif