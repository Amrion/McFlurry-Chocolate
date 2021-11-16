#pragma once

#include <vector>
#include "matrix.h"

using namespace std;

class NMF {
private:
    const int min_matrix_value = 0;
    const int max_matrix_value = 10;

    void gradient_descent(matrix<int>& A, matrix<float>& W, matrix<float>& H);
public:
    NMF() = default;
    ~NMF() = default;

    matrix<float> matrix_factorization(matrix<int>& A, int k);
};

