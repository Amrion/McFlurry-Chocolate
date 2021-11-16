#include <bits/stdc++.h>

#include "matrix.h"

using namespace std;

template<class T>
matrix<T>::matrix(const int _n, const int _m) {
    n = _n;
    m = _m;
    for (int i = 0; i < n; ++i) {
        data.push_back(vector<T>(m));
    }
}

template<class T>
matrix<T>::matrix(const vector<vector<int>>& A) {
    assert(A.size() > 0);
    assert(A[0].size() > 0);
    n = A.size();
    m = A[0].size();
    for (size_t i = 0; i < A.size(); ++i) {
        data.push_back(vector<T>(A[i].size()));
        for (size_t j = 0; j < A[i].size(); ++j) {
            data[i][j] = static_cast<T>( A[i][j] );
        }
    }
}

template<class T>
matrix<T>::~matrix() {
    for (int i = 0; i < size_n(); ++i)
        data[i].clear();
    data.clear();
}

template<class T>
matrix<T> matrix<T>::operator* (const matrix<T>& B) const {
    assert(size_m() == B.size_n());
    matrix<T> P(size_n(), B.size_m());
    for (int i = 0; i < size_n(); ++i) {
        for (int j = 0; j < B.size_m(); ++j) {
            for (int k = 0; k < size_m(); ++k) {
                P[i][j] += data[i][k] * B.data[k][j];
            }
        }
    }
    return P;
}

template<class T>
matrix<T> matrix<T>::operator* (const float num) const {
    matrix<T> P(size_n(), size_m());
    for (int i = 0; i < size_n(); ++i) {
        for (int j = 0; j < size_m(); ++j) {
            P[i][j] = data[i][j] * num;
        }
    }
    return P;
}

template<class T>
matrix<T> matrix<T>::operator+ (const matrix<T>& B) const {
    assert(size_n() == B.size_n());
    assert(size_m() == B.size_m());
    matrix<T> P(size_n(), size_m());
    for (int i = 0; i < size_n(); ++i) {
        for (int j = 0; j < size_m(); ++j) {
            P[i][j] = data[i][j] + B.data[i][j];
        }
    }
    return P;
}

template<class T>
T matrix<T>::random_in_range(const T& l, const T& r) {
    return l + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(r-l)));
}

template<class T>
void matrix<T>::random_init(const T& l, const T& r) {
    assert(n != 0 && m != 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            data[i][j] = random_in_range(l, r);
        }
    }
}

template<class T>
pair<int, int> matrix<T>::size() {
    return {n, m};
}

template<class T>
const int matrix<T>::size_n() const {
    return n;
}

template<class T>
const int matrix<T>::size_m() const {
    return m;
}

template<class T>
matrix<T> matrix<T>::_T() {
    matrix<T> A_T(size_m(), size_n());
    for (int i = 0; i < size_n(); ++i) {
        for (int j = 0; j < size_m(); ++j) {
            A_T[j][i] = data[i][j];
        }
    }
    return A_T;
}

template class matrix<float>;
