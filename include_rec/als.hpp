#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

class ALS {
private:
    const int l_value = 0;
    const int r_value = 10;
    int k;
    float eps;
    float learning_rate;
    float nb_epoch;
    bool use_reg;
public:
    ALS();
    ALS(const int _k, float _eps=0.01, float _learning_rate=0.5, int _nb_epoch=0, bool use_reg=true);
    ~ALS() = default;

    void random_init(matrix<float>& A, const float l, const float r);
    float euclidean_norm(const matrix<float>& A);
    float frabenius_norm(const matrix<float>& A, const matrix<float>& W, const matrix<float>& H);
    void gradient_descent(const matrix<float>& A, matrix<float>& W, matrix<float>& H);
    void gradient_descent_reg(const matrix<float>& A, matrix<float>& W, matrix<float>& H);
    matrix<float> matrix_factorization(matrix<float>& A);
};
