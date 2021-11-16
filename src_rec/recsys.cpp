#include <bits/stdc++.h>

#include "recsys.h"

using namespace std;

matrix<float> RecSys::create_recommendations(vector<vector<int>>& V, int k) {
    NMF model;
    
    matrix<float> A(V);
    matrix<float> REC = model.matrix_factorization(A, k);

    return REC;
}
