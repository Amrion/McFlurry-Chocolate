#include <bits/stdc++.h>

#include "matrix.h"

using namespace std;

template<class T, class F>
matrix<T, F>::matrix(const int _n, const int _m) {
    n = _n;
    m = _m;
    for (int i = 0; i < n; ++i) {
        data.push_back(vector<T>(m));
    }
}

template<class T, class F>
matrix<T, F>::~matrix() {
    data.clear();
}

template<class T, class F>
T matrix<T, F>::random_in_range(const T& l, const T& r) {
    return l + static_cast <T> (rand()) /( static_cast <T> (RAND_MAX/(r-l)));
}

template<class T, class F>
matrix<T, F>::matrix(const vector<vector<F>>& A) {
    for (size_t i = 0; i < A.size(); ++i) {
        data.push_back(vector<T>());
        for (size_t j = 0; j < A[i].size(); ++j) {
            data[i].push_back(static_cast<T>(A[i][j]));
        }
    }
}

template<class T, class F>
void matrix<T, F>::random_init(const T& l, const T& r) {
    assert(n != 0 && m != 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            data[i][j] = random_in_range(l, r);
        }
    }
}

template<class T, class F>
pair<int, int> matrix<T, F>::size() {
    return {n, m};
}

template<class T, class F>
const int matrix<T, F>::size_n() const {
    return n;
}

template<class T, class F>
const int matrix<T, F>::size_m() const {
    return m;
}

template<class T, class F>
matrix<T> matrix<T, F>::_T() {
    matrix<T> A_T(size_m(), size_n());
    for (int i = 0; i < size_n(); ++i) {
        for (int j = 0; j < size_m(); ++j) {
            A_T[j][i] = data[i][j];
        }
    }
    return A_T;
}



template class matrix<int>;
template class matrix<float>;
