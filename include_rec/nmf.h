#pragma once

#include <vector>
#include "matrix.h"

using namespace std;

class NMF {
private:
    const int l_value = 0;
    const int r_value = 10;
    int k;
    float eps;
    float learning_rate;
    float nb_epoch;
public:
    float Euclidean_norm(matrix<float>& A);
    float Frabenius_norm(matrix<float>& A, matrix<float>& W, matrix<float>& H);
    void gradient_descent(matrix<float>& A, matrix<float>& W, matrix<float>& H);
    NMF();
    NMF(const int _k, float _eps=0.01, float _learning_rate=0.5, int _nb_epoch=0);
    ~NMF() = default;

    matrix<float> matrix_factorization(matrix<float>& A);
};

