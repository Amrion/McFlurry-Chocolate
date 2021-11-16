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
matrix<T>::~matrix() {
    data.clear();
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
int matrix<T>::size_n() {
    return n;
}

template<class T>
int matrix<T>::size_m() {
    return m;
}



template class matrix<int>;
template class matrix<float>;
