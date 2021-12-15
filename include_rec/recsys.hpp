#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <map>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

#include "als.hpp"
#include "dbscan.hpp"

using namespace boost::numeric::ublas;

class RecSys {
   private:
    std::mutex mu;
    const unsigned max_thread = 100;

    DBScan cluster_model;
    std::shared_ptr<std::map<int, std::vector<int>>> recs;

    matrix<float> create_matrix(const std::vector<std::vector<int>>& V);

    void shared_assignment(
        std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
        const std::vector<int>& recs, const int user_id);

    void rec_for_user(
        std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
        const matrix<float>& REC, const int user_id, const int user_i,
        std::vector<int>& users_id);

    void rec_multi_thread(
        const int n_jobs, std::vector<std::thread>& threads, const int i,
        std::shared_ptr<std::map<int, std::vector<int>>> user_recs,
        const matrix<float>& REC, std::vector<int>& users_id);

   public:
    RecSys() = default;
    ~RecSys() = default;

    void fit(const std::vector<std::vector<int>>& V,
             std::vector<std::vector<float>>* X,

             std::vector<int> users_id = std::vector<int>(0), int _k = 5,
             float _eps = 0.01, float _learning_rate = 0.5, int _nb_epoch = 0,
             int n_jobs = -1, bool use_reg = true,

             float cl_eps = 2.5, size_t min_sample = 4);

    std::shared_ptr<std::map<int, std::vector<int>>> fit_predict(
        const std::vector<std::vector<int>>& V,
        std::vector<int> users_id = std::vector<int>(0),

        int _k = 5, float _eps = 0.01, float _learning_rate = 0.5,
        int _nb_epoch = 0, int n_jobs = -1, bool use_reg = true);

    std::vector<int> predict(const int user_id);
    std::vector<int> predict(const std::vector<float>& user_values);
};
