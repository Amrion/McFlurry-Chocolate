#pragma once

#include <bits/stdc++.h>
#include <thread>
#include <mutex>

#include <boost/numeric/ublas/matrix.hpp>
#include "nmf.hpp"

using namespace boost::numeric::ublas;

class RecSys {
private:
    std::mutex mu;

    matrix<float> create_matrix(const std::vector<std::vector<int>>& V);

    void shared_assignment(
        std::map<int, std::vector<int>>& user_recs, 
        const std::vector<int>& recs, 
        const int user_id);
    void rec_for_user(
        std::map<int, std::vector<int>>& user_recs, 
        matrix<float>& REC, 
        const int user_id);
public:
    std::map<int, std::vector<int>> create_recommendations(
        const std::vector<std::vector<int>>& V, 
        int _k=5, 
        float _eps=0.01, 
        float _learning_rate=0.5, 
        int _nb_epoch=0, 
        int n_jobs=-1);
};
