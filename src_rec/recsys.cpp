#include "recsys.hpp"


void print_matrix(matrix<float>& A) {
    for (size_t i = 0; i < A.size1(); ++i) {
        for (size_t j = 0; j < A.size2(); ++j) {
            std::cout << A(i, j) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "-----------------------------\n";
}


matrix<float> RecSys::create_matrix(const std::vector<std::vector<int>>& V) {
    assert(V.size() > 0);
    assert(V[0].size() > 0);
    matrix<float> A(V.size(), V[0].size());
    for (size_t i = 0; i < V.size(); ++i) {
        for (size_t j = 0; j < V[i].size(); ++j) {
            A(i, j) = static_cast<float>( V[i][j] );
        }
    }
    return A;
}

void RecSys::shared_assignment(std::map<int, std::vector<int>>& user_recs, const std::vector<int>& recs, const int user_id) {
    mu.lock();
    user_recs[user_id] = recs;
    mu.unlock();
}

struct id_score {
    id_score(std::pair<int, float> _i_s) {
        i_s = _i_s;
    }
    std::pair<int, float> i_s;
    bool operator< (const id_score& r) const {
        return i_s.second > r.i_s.second;
    }
};

void RecSys::rec_for_user(std::map<int, std::vector<int>>& user_recs, matrix<float>& REC, const int user_id) {
    std::vector<id_score> rec_ids;
    for (size_t i = 0; i < REC.size2(); ++i)
        rec_ids.push_back( id_score({i, REC(user_id, i)}) );
    
    sort(rec_ids.begin(), rec_ids.end());
    std::vector<int> recs(REC.size2());
    for (size_t i = 0; i < REC.size2(); ++i) {
        recs[i] = rec_ids[i].i_s.first;
    }
    rec_ids.clear();
    shared_assignment(user_recs, recs, user_id);
}

std::map<int, std::vector<int>> RecSys::create_recommendations(const std::vector<std::vector<int>>& V, int _k, float _eps, float _learning_rate, int _nb_epoch, int n_jobs, bool use_reg, const std::vector<int>& users_id) {
    assert(_k > 0);
    ALS model(_k, _eps=_eps, _learning_rate=_learning_rate, _nb_epoch=_nb_epoch, use_reg=use_reg);
    
    matrix<float> A = create_matrix(V);
    print_matrix(A);

    matrix<float> REC = model.matrix_factorization(A);
    print_matrix(REC);

    std::map<int, std::vector<int>> user_recs;

    std::vector<std::thread> threads;

    if (users_id.size() != 0) 
        assert(users_id.size() == REC.size1());
    
    for (size_t i = 0; i < REC.size1(); ++i) {
        // threads.push_back(std::thread(&RecSys::rec_for_user, this, user_recs, REC, i));
        rec_for_user(user_recs, REC, (users_id.size() != 0) ? users_id[i] : i);
    }

    for (auto &th : threads) {
        th.join();
    }
    
    return user_recs;
}
