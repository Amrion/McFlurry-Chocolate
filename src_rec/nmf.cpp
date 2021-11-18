#include <bits/stdc++.h>

#include "matrix.hpp"
#include "nmf.hpp"

#define mi matrix<int>
#define mf matrix<float>

using namespace std;

void print_m(mf& A) {
    for (size_t i = 0; i < A.size_n(); ++i) {
        for (size_t j = 0; j < A.size_m(); ++j) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "-----------------------------\n";
}

NMF::NMF() {
    srand(time(NULL));
    k = 5;
    eps = 0.01;
    learning_rate = 0.5;
    nb_epoch = 0;
}

NMF::NMF(const int _k, float _eps, float _learning_rate, int _nb_epoch) {
    srand(time(NULL));
    k = _k;
    eps = _eps;
    learning_rate = _learning_rate;
    nb_epoch = _nb_epoch;
}

float NMF::Euclidean_norm(mf& A) {
    float sum = 0;
    for (size_t i = 0; i < A.size_n(); ++i) {
        for (size_t j = 0; j < A.size_m(); ++j) {
            sum += pow(A[i][j], 2);
        }
    }
    return 0.5 * sqrt( sum );
}

float NMF::Frabenius_norm(mf& A, mf& W, mf& H) {
    mf WH = W * H * (-1) + A;
    float sum = 0;
    for (size_t i = 0; i < WH.size_n(); ++i) {
        for (size_t j = 0; j < WH.size_m(); ++j) {
            sum += pow(WH[i][j], 2);
        }
    }
    return 0.5 * sqrt( sum );
}

void NMF::gradient_descent(mf& A, mf& W, mf& H) {

    int epoch_i = 0;
    float error = 0;
    do {
        error = Frabenius_norm(A, W, H);

        mf grad_w = ( W*H + (A * -1) ) * (H._T());
        mf HHT = H * H._T();
        float t_w = 1 / Euclidean_norm(HHT);

        mf grad_h = (W._T()) * ( W*H + (A * -1) );
        mf WTW = W._T() * W;
        float t_h = 1 / Euclidean_norm(WTW);


        W = W + ( grad_w * (learning_rate * t_w * -1) );
        H = H + ( grad_h * (learning_rate * t_h * -1) );

        if (nb_epoch != 0 && epoch_i == nb_epoch)
            break;
        ++epoch_i;
    } while (error - Frabenius_norm(A, W, H) > eps);

}

mf NMF::matrix_factorization(mf& A) {
    assert(A.size().first != 0);
    assert(A.size().second != 0);

    const int n = A.size().first;
    const int m = A.size().second;

    mf W(n, k); W.random_init(l_value, r_value);
    mf H(k, m); H.random_init(l_value, r_value);

    gradient_descent(A, W, H);
    
    matrix<float> REC = W * H;
    return REC;
}
