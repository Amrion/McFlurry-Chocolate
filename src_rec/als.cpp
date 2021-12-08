#include "als.hpp"

using namespace boost::numeric::ublas;

ALS::ALS(const int _k, float _eps, float _learning_rate, int _nb_epoch,
         bool _use_reg) {
    srand(time(NULL));
    k = _k;
    eps = _eps;
    learning_rate = _learning_rate;
    nb_epoch = _nb_epoch;
    use_reg = _use_reg;
}

void ALS::random_init(matrix<float>& A, const float l, const float r) {
    for (size_t i = 0; i < A.size1(); ++i) {
        for (size_t j = 0; j < A.size2(); ++j) {
            A(i, j) = l + static_cast<float>(rand()) /
                              (static_cast<float>(RAND_MAX / (r - l)));
        }
    }
}

float ALS::euclidean_norm(const matrix<float>& A) {
    float sum = 0;
    for (size_t i = 0; i < A.size1(); ++i) {
        for (size_t j = 0; j < A.size2(); ++j) {
            sum += pow(A(i, j), 2);
        }
    }
    return 0.5 * sqrt(sum);
}

float ALS::frabenius_norm(const matrix<float>& A, const matrix<float>& W,
                          const matrix<float>& H) {
    matrix<float> WH = prod(W, H) * (-1) + A;
    float sum = 0;
    for (size_t i = 0; i < WH.size1(); ++i) {
        for (size_t j = 0; j < WH.size2(); ++j) {
            sum += pow(WH(i, j), 2);
        }
    }
    return 0.5 * sqrt(sum);
}

void ALS::gradient_descent(const matrix<float>& A, matrix<float>& W,
                           matrix<float>& H) {
    int epoch_i = 0;
    float error = 0;

    do {
        error = frabenius_norm(A, W, H);

        matrix<float> grad_w = prod(prod(W, H) + A * -1, trans(H));
        matrix<float> HHT = prod(H, trans(H));
        float t_w = 1 / euclidean_norm(HHT);
        W = W + (grad_w * (learning_rate * t_w * -1));

        matrix<float> grad_h = prod(trans(W), prod(W, H) + (A * -1));
        matrix<float> WTW = prod(trans(W), W);
        float t_h = 1 / euclidean_norm(WTW);
        H = H + (grad_h * (learning_rate * t_h * -1));

        if (nb_epoch != 0 && epoch_i == nb_epoch) break;
        ++epoch_i;
    } while (error - frabenius_norm(A, W, H) > eps);
}

void ALS::gradient_descent_reg(const matrix<float>& A, matrix<float>& W,
                               matrix<float>& H) {
    int epoch_i = 0;
    float error = 0;

    do {
        error = frabenius_norm(A, W, H);

        matrix<float> grad_w = prod(prod(W, H) - A, trans(H));
        matrix<float> HHT = prod(H, trans(H));
        float t_w = 1 / euclidean_norm(HHT);
        W = W + (grad_w * (learning_rate * t_w * -1));

        matrix<float> grad_h = prod(trans(W), prod(W, H) + (A * -1));
        matrix<float> WTW = prod(trans(W), W);
        float t_h = 1 / euclidean_norm(WTW);
        H = H + (grad_h * (learning_rate * t_h * -1));

        if (nb_epoch != 0 && epoch_i == nb_epoch) break;
        ++epoch_i;
    } while (error - frabenius_norm(A, W, H) > eps);
}

void ALS::fit(matrix<float>& A) {
    assert(A.size1() != 0);
    assert(A.size2() != 0);

    const int n = A.size1();
    const int m = A.size2();

    matrix<float> W(n, k);
    random_init(W, l_value, r_value);
    matrix<float> H(k, m);
    random_init(H, l_value, r_value);

    if (use_reg)
        gradient_descent_reg(A, W, H);
    else
        gradient_descent(A, W, H);

    REC = prod(W, H);
}

matrix<float> ALS::predict() { return REC; }