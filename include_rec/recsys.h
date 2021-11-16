#pragma once

#include <vector>

#include "matrix.h"
#include "nmf.h"

using namespace std;

class RecSys {
private:
    NMF model;
public:
    matrix<float> create_recommendations(vector<vector<int>>& A, int k);
};
