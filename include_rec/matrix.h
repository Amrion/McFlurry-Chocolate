#pragma once

#include <bits/stdc++.h>

using namespace std;

template<class T, class F = int>
class matrix {
private:
    int n = 0;
    int m = 0;
    vector<vector<T>> data;

    T random_in_range(const T& l, const T& r);
public:
    matrix() = default;
    matrix(const int n, const int m);
    matrix(const vector<vector<F>>& A);
    ~matrix();

    vector<T>& operator[] (int i) { return data[i]; }

    matrix<T> operator* (const matrix<T>& B) const {
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
    matrix<T> operator* (const float num) const {
        matrix<T> P(size_n(), size_m());
        for (int i = 0; i < size_n(); ++i) {
            for (int j = 0; j < size_m(); ++j) {
                P[i][j] = data[i][j] * num;
            }
        }
        return P;
    }

    matrix<T> operator+ (const matrix<T>& B) const {
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

    pair<int, int> size();
    const int size_n() const;
    const int size_m() const;
    void random_init(const T& l, const T& r);
    matrix<T> _T();
};
