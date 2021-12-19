#include "recsys.hpp"

matrix<float> RecSys::create_matrix(const std::vector<std::vector<int>>& V) {
    assert(V.size() > 0);
    assert(V[0].size() > 0);
    matrix<float> A(V.size(), V[0].size());
    for (size_t i = 0; i < V.size(); ++i) {
        for (size_t j = 0; j < V[i].size(); ++j) {
            A(i, j) = static_cast<float>(V[i][j]);
        }
    }
    return A;
}

void RecSys::shared_assignment(
    std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
    const std::vector<int>& recs, const int user_id) {
    mu.lock();
    (*user_recs)[user_id] = recs;
    mu.unlock();
}

struct id_score {
    id_score(std::pair<int, float> _i_s) { i_s = _i_s; }
    std::pair<int, float> i_s;
    bool operator<(const id_score& r) const {
        return i_s.second > r.i_s.second;
    }
};

void RecSys::rec_for_user(
    std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
    const matrix<float>& REC, const int user_id, const int user_i,
    std::vector<int>& users_id) {
    // Here we sum score of ALS + Similarity of TfIdf Model
    std::vector<id_score> rec_ids;
    for (size_t i = 0; i < REC.size2(); ++i)
        rec_ids.push_back(id_score(
            {users_id[i], REC(user_i, i) + text_model.predict(users_id[user_id],
                                                              users_id[i])}));

    sort(rec_ids.begin(), rec_ids.end());
    std::vector<int> recs(REC.size2());
    for (size_t i = 0; i < REC.size2(); ++i) {
        recs[i] = rec_ids[i].i_s.first;
    }
    rec_ids.clear();
    shared_assignment(user_recs, recs, user_id);
}

void RecSys::rec_multi_thread(
    const int n_jobs, std::vector<std::thread>& threads, const int i,
    std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
    const matrix<float>& REC, std::vector<int>& users_id) {
    if (n_jobs == -1) {
        if ((i + 1) % max_thread != 0) {
            threads.push_back(
                std::thread([user_recs, REC, i, &users_id, this]() {
                    rec_for_user(user_recs, REC, users_id[i], i, users_id);
                }));
        } else {
            for (auto& th : threads) {
                th.join();
            }
            threads.clear();
            threads.push_back(
                std::thread([user_recs, REC, i, &users_id, this]() {
                    rec_for_user(user_recs, REC, users_id[i], i, users_id);
                }));
        }
    } else if (n_jobs > 0) {
        if ((i + 1) % n_jobs != 0) {
            threads.push_back(
                std::thread([user_recs, REC, i, &users_id, this]() {
                    rec_for_user(user_recs, REC, users_id[i], i, users_id);
                }));
        } else {
            for (auto& th : threads) {
                th.join();
            }
            threads.clear();
            threads.push_back(
                std::thread([user_recs, REC, i, &users_id, this]() {
                    rec_for_user(user_recs, REC, users_id[i], i, users_id);
                }));
        }
    } else {
        rec_for_user(user_recs, REC, users_id[i], i, users_id);
    }
}

void RecSys::fit(const std::vector<std::vector<int>>& V,
                 std::vector<std::vector<float>>* X,
                 std::list<std::string>& corpus, std::vector<int> users_id,
                 int _k, float _eps, float _learning_rate, int _nb_epoch,
                 int n_jobs, float cl_eps, size_t min_sample) {
    // TfIdf Cosine similarity for users description
    text_model.fit(corpus, users_id);

    // ALS matrix factorization
    recs =
        fit_predict(V, users_id, _k, _eps, _learning_rate, _nb_epoch, n_jobs);

    // DBSCAN Clustering
    cluster_model = DBScan(cl_eps, min_sample, users_id);
    cluster_model.fit(X);
}

std::vector<int> RecSys::predict(const int user_id) {
    if ((*recs).find(user_id) == (*recs).end()) {
        return std::vector<int>(0);
    }
    std::vector<int> als_recs = (*recs)[user_id];
    std::vector<int> dbscan_recs = cluster_model.predict(user_id);

    std::vector<int> recs;

    auto const predicate = [&dbscan_recs](int const value) {
        return std::find(dbscan_recs.begin(), dbscan_recs.end(), value) !=
               dbscan_recs.end();
    };

    auto const not_predicate = [&dbscan_recs](int const value) {
        return std::find(dbscan_recs.begin(), dbscan_recs.end(), value) ==
               dbscan_recs.end();
    };

    std::copy_if(als_recs.begin(), als_recs.end(), std::back_inserter(recs),
                 predicate);
    std::copy_if(als_recs.begin(), als_recs.end(), std::back_inserter(recs),
                 not_predicate);

    return recs;
}

std::vector<int> RecSys::predict(const std::vector<float>& user_values) {
    return cluster_model.predict(user_values);
}

std::shared_ptr<std::map<int, std::vector<int>>> RecSys::fit_predict(
    const std::vector<std::vector<int>>& V, std::vector<int> users_id, int _k,
    float _eps, float _learning_rate, int _nb_epoch, int n_jobs) {
    assert(_k > 0);
    ALS model(_k, _eps = _eps, _learning_rate = _learning_rate,
              _nb_epoch = _nb_epoch);
    DBScan cluster;

    matrix<float> A = create_matrix(V);
    // print_matrix(A);

    model.fit(A);
    matrix<float> REC = model.predict();
    // print_matrix(REC);

    std::shared_ptr<std::map<int, std::vector<int>>> user_recs =
        std::make_shared<std::map<int, std::vector<int>>>();

    if (users_id.size() != 0)
        assert(users_id.size() == REC.size1());
    else {
        users_id = std::vector<int>(REC.size1());
        std::iota(std::begin(users_id), std::end(users_id), 0);
    }

    std::vector<std::thread> threads;
    for (size_t i = 0; i < REC.size1(); ++i) {
        rec_multi_thread(n_jobs, threads, i, user_recs, REC, users_id);
    }

    for (auto& th : threads) {
        th.join();
    }

    return user_recs;
}
