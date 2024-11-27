#ifndef IMPPARALLEL_H
#define IMPPARALLEL_H

#include "optimizedmatrix.h"

bool checkSymimp(const optimized_matrix& mat);

void matTransposeimp(const optimized_matrix& mat, optimized_matrix& transposed);

#endif