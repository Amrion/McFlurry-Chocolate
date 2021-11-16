#include <bits/stdc++.h>

#include "matrix.h"
#include "nmf.h"

#define mi matrix<int>
#define mf matrix<float>

using namespace std;

float sqr(const float x) {
    return x * x;
}

float NMF::Euclidean_norm(mf& A) {
    float sum = 0;
    for (int i = 0; i < A.size_n(); ++i) {
        for (int j = 0; j < A.size_m(); ++j) {
            sum += sqr(A[i][j]);
        }
    }
    return 0.5 * sqrt( sum );
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

void print_m(mf& A) {
    for (int i = 0; i < A.size_n(); ++i) {
        for (int j = 0; j < A.size_m(); ++j) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "-----------------------------\n";
}

void NMF::gradient_descent(mf& A, mf& W, mf& H) {
    const float learning_rate = 0.05;
    const float eps = 0.001;

    float error = 0;
    do {
        error = Frabenius_norm(A, W, H);

        // cout << "FN 0 = " << error << '\n';
        // cout << "W 0 :: \n";
        // print_m(W);
        // cout << "H 0 :: \n";
        // print_m(H);
        // mf WH = W * H;
        // cout << "WH 0 :: \n";
        // print_m(WH);


        mf grad_w = ( W*H + (A * -1) ) * (H._T());
        mf HHT = H * H._T();
        float t_w = 1 / Euclidean_norm(HHT);

        mf grad_h = (W._T()) * ( W*H + (A * -1) );
        mf WTW = W._T() * W;
        float t_h = 1 / Euclidean_norm(WTW);


        // cout << "grad_W :: \n";
        // print_m(grad_w);
        // cout << "grad_H :: \n";
        // print_m(grad_h);
        // cout << "t_W :: " << t_w << '\n';
        // cout << "t_H :: " << t_h << '\n';
        

        
        W = W + ( grad_w * (learning_rate * t_w * -1) );
        H = H + ( grad_h * (learning_rate * t_h * -1) );

        // cout << "FN 1 = " << error << '\n';
        // cout << "W 1 :: \n";
        // print_m(W);
        // cout << "H 1 :: \n";
        // print_m(H);
        // WH = W * H;
        // cout << "WH 1 :: \n";
        // print_m(WH);

        // cout << "ERROR DESCENT :: " << error - Frabenius_norm(A, W, H) << '\n';
        // int step; cin >> step;

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
    
    matrix<float> REC = W * H;
    return REC;
}