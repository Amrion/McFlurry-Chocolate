#include <bits/stdc++.h>

#include "matrix.h"
#include "nmf.h"

#define mi matrix<int>
#define mf matrix<float>

using namespace std;

float sqr(const float x) {
    return x * x;
}

float NMF::Frabenius_norm(mf& A, mf& W, mf& H) {
    mf WH = W * H * (-1) + A;
    float sum = 0;
    for (int i = 0; i < WH.size_n(); ++i) {
        for (int j = 0; j < WH.size_m(); ++j) {
            sum += sqr(WH[i][j]);
        }
    }
    return 0.5 * sqrt( sum );
}

void NMF::gradient_descent(mf& A, mf& W, mf& H) {
    const float learning_rate = 0.5;
    const float eps = 0.01;

    float error = Frabenius_norm(A, W, H);
    int i = 0;
    do {
        mf grad_w = (W._T() * A) + (W._T() * W * H * (-1));
        mf grad_h = (A * H._T()) + (W * H * H._T() * (-1));
        cout << "HERE :: " << i << '\n';
        
        W = W + grad_w._T() * (-learning_rate);
        H = H + grad_h._T() * (-learning_rate);
        i++;
        cout << error - Frabenius_norm(A, W, H) << '\n';
    } while (error - Frabenius_norm(A, W, H) > eps);

}

mf NMF::matrix_factorization(mf& A, int k) {
    assert(A.size().first != 0);
    assert(A.size().second != 0);
    assert(k > 0);

    const int n = A.size().first;
    const int m = A.size().second;

    mf W(n, k); W.random_init(min_matrix_value, max_matrix_value);
    mf H(k, m); H.random_init(min_matrix_value, max_matrix_value);

    gradient_descent(A, W, H);
    
    return W * H;
}