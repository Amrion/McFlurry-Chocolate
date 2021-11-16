#pragma once

#include <vector>

#include "matrix.h"
#include "nmf.h"

using namespace std;

class RecSys {
public:
    matrix<float> create_recommendations(vector<vector<int>>& A, int k);
};
