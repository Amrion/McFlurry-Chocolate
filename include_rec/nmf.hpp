#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

class NMF {
private:
    const int l_value = 0;
    const int r_value = 10;
    int k;
    float eps;
    float learning_rate;
    float nb_epoch;
public:
    NMF();
    NMF(const int _k, float _eps=0.01, float _learning_rate=0.5, int _nb_epoch=0);
    ~NMF() = default;

    void random_init(matrix<float>& A, const float l, const float r);
    float Euclidean_norm(const matrix<float>& A);
    float Frabenius_norm(const matrix<float>& A, const matrix<float>& W, const matrix<float>& H);
    void gradient_descent(matrix<float>& A, matrix<float>& W, matrix<float>& H);
    matrix<float> matrix_factorization(matrix<float>& A);
};
