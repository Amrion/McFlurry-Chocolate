#pragma once

#include <bits/stdc++.h>

using namespace std;

template<class T>
class matrix {
private:
    size_t n = 0;
    size_t m = 0;
    vector<vector<T>> data;

    T random_in_range(const T& l, const T& r);
public:
    matrix() = default;
    matrix(const int n, const int m);
    matrix(const vector<vector<int>>& A);
    ~matrix();

    vector<T>& operator[] (int i) { return data[i]; }
    matrix<T> operator* (const matrix<T>& B) const;
    matrix<T> operator* (const float num) const;
    matrix<T> operator+ (const matrix<T>& B) const;

    pair<size_t, size_t> size() const;
    const size_t size_n() const;
    const size_t size_m() const;
    void random_init(const T& l, const T& r);
    matrix<T> _T();
};
