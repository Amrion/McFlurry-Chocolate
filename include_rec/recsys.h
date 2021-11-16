#pragma once

#include <bits/stdc++.h>
#include <thread>
#include <mutex>

#include "matrix.h"
#include "nmf.h"

using namespace std;

class RecSys {
private:
    mutex mu;

    void shared_assignment(map<int, vector<int>>& user_recs, const vector<int>& recs, const int user_id);
    void rec_for_user(map<int, vector<int>>& user_recs, matrix<float>& REC, const int user_id);
public:
    map<int, vector<int>> create_recommendations(vector<vector<int>>& V, int _k=5, float _eps=0.01, float _learning_rate=0.5, int _nb_epoch=0, int n_jobs=-1);
};
