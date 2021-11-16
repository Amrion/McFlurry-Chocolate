#pragma once

#include <bits/stdc++.h>

using namespace std;

template<class T>
class matrix {
private:
    int n = 0;
    int m = 0;
    vector<vector<T>> data;

    T random_in_range(const T& l, const T& r);
public:
    matrix() = default;
    matrix(const int n, const int m);
    ~matrix();

    vector<T>& operator[] (const int i) { return data[i]; }

    pair<int, int> size();
    int size_n();
    int size_m();
    void random_init(const T& l, const T& r);
};
