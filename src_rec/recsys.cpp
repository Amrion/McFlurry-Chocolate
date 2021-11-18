#include "recsys.hpp"

using namespace std;

void print_matrix(matrix<float>& A) {
    for (size_t i = 0; i < A.size_n(); ++i) {
        for (size_t j = 0; j < A.size_m(); ++j) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "-----------------------------\n";
}

void RecSys::shared_assignment(map<int, vector<int>>& user_recs, const vector<int>& recs, const int user_id) {
    mu.lock();
    user_recs[user_id] = recs;
    mu.unlock();
}

struct id_score {
    id_score(pair<int, float> _i_s) {
        i_s = _i_s;
    }
    pair<int, float> i_s;
    bool operator< (const id_score& r) const {
        return i_s.second > r.i_s.second;
    }
};

void RecSys::rec_for_user(map<int, vector<int>>& user_recs, matrix<float>& REC, const int user_id) {
    vector<id_score> rec_ids;
    for (size_t i = 0; i < REC.size_m(); ++i)
        rec_ids.push_back( id_score({i, REC[user_id][i]}) );
    
    sort(rec_ids.begin(), rec_ids.end());
    vector<int> recs(REC.size_m());
    for (size_t i = 0; i < REC.size_m(); ++i) {
        recs[i] = rec_ids[i].i_s.first;
    }
    rec_ids.clear();
    shared_assignment(user_recs, recs, user_id);
}

map<int, vector<int>> RecSys::create_recommendations(vector<vector<int>>& V, int _k, float _eps, float _learning_rate, int _nb_epoch, int n_jobs) {
    assert(_k > 0);
    NMF model(_k, _eps=_eps, _learning_rate=_learning_rate, _nb_epoch=_nb_epoch);
    
    matrix<float> A(V);
    print_matrix(A);

    matrix<float> REC = model.matrix_factorization(A);
    print_matrix(REC);

    map<int, vector<int>> user_recs;

    vector<thread> threads;
    for (size_t i = 0; i < REC.size_n(); ++i) {
        // threads.push_back(thread(&RecSys::rec_for_user, this, user_recs, REC, i));
        rec_for_user(user_recs, REC, i);
    }

    for (auto &th : threads) {
        th.join();
    }
    
    return user_recs;
}
