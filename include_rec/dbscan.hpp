#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <numeric>
#include <vector>

const int UNCLASSIFIED = -1;
const int SUCCESS = 0;
const int NOISE = -2;
const int FAILURE = -3;

struct point {
    int user_id;
    size_t i;
    int cluster_id;

    point();
    point(int _user_id, size_t _i, int _cluster_id = UNCLASSIFIED);
    ~point() = default;
};

class DBScan {
   private:
    float eps;
    size_t min_sample;
    std::vector<int> users_id;
    std::vector<point> points;
    std::vector<std::vector<float>>* X;

    inline float calculate_distance(const point& p1, const point& p2);
    inline float calculate_distance(const std::vector<float>& p1,
                                    const point& p2);
    std::vector<int> calculate_cluster(point& p);
    int expand_cluster(point& p, int cluster_id);
    bool points_equal(const point& p1, const point& p2);

    std::vector<int> create_predictions(const int user_cluster_id);

   public:
    DBScan(float _eps = 2.5, size_t _min_sample = 4,
           std::vector<int> _users_id = std::vector<int>(0));
    ~DBScan();

    void fit(std::vector<std::vector<float>>* _X);
    std::vector<int> predict();
    std::vector<int> predict(const int user_id);
    std::vector<int> predict(const std::vector<float>& user_values);
};
