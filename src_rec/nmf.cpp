#include <bits/stdc++.h>

#include "matrix.h"
#include "nmf.h"

#define mi matrix<int>
#define mf matrix<float>

using namespace std;


void NMF::gradient_descent(mi& A, mf& W, mf& H) {
    

}

mf NMF::matrix_factorization(mi& A, int k) {
    assert(A.size().first != 0);
    assert(A.size().second != 0);
    assert(k > 0);

    const int n = A.size().first;
    const int m = A.size().second;

    mf W(n, k); W.random_init(min_matrix_value, max_matrix_value);
    mf H(k, m); H.random_init(min_matrix_value, max_matrix_value);

    gradient_descent(A, W, H);
    

    return W;
}