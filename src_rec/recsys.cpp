#include <bits/stdc++.h>

#include "matrix.h"
#include "nmf.h"

#define vi vector<int>
#define vii vector<vector<int>>

using namespace std;

class RecSys {
private:
    NMF model;
public:
    vii create_recommendations(vii& A, int k);
};
