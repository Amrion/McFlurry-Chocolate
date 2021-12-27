#include "dbscan.hpp"

point::point() { cluster_id = UNCLASSIFIED; }

point::point(int _user_id, size_t _i, int _cluster_id) {
    user_id = _user_id;
    i = _i;
    cluster_id = _cluster_id;
}

DBScan::DBScan(float _eps, size_t _min_sample, std::vector<int> _users_id) {
    eps = _eps;
    min_sample = _min_sample;
    users_id = _users_id;
    points = std::vector<point>(0);
}

void DBScan::set_params(float _eps, size_t _min_sample,
                        std::vector<int> _users_id) {
    eps = _eps;
    min_sample = _min_sample;
    users_id = _users_id;
}

void DBScan::fit(std::shared_ptr<std::vector<std::vector<float>>> _X) {
    assert(_X->size() > 0);
    X = _X;
    if (users_id.size() == 0) {
        users_id = std::vector<int>(X->size());
        std::iota(std::begin(users_id), std::end(users_id), 0);
    }

    for (size_t i = 0; i < X->size(); ++i) {
        point p(users_id[i], i);
        points.push_back(p);
    }

    int cluster_id = 1;
    std::vector<point>::iterator iter;
    for (iter = points.begin(); iter != points.end(); ++iter) {
        if (iter->cluster_id == UNCLASSIFIED) {
            if (expand_cluster(*iter, cluster_id) != FAILURE) {
                cluster_id += 1;
            }
        }
    }
}

int DBScan::expand_cluster(point& p, int cluster_id) {
    std::vector<int> clusterSeeds = calculate_cluster(p);

    if (clusterSeeds.size() < min_sample) {
        p.cluster_id = NOISE;
        return FAILURE;
    }

    int idx = 0;
    int indexCorePoint = 0;
    std::vector<int>::iterator iterSeeds;

    for (iterSeeds = clusterSeeds.begin(); iterSeeds != clusterSeeds.end();
         ++iterSeeds) {
        points.at(*iterSeeds).cluster_id = cluster_id;
        if (points_equal(points.at(*iterSeeds), p)) {
            indexCorePoint = idx;
        }
        ++idx;
    }
    clusterSeeds.erase(clusterSeeds.begin() + indexCorePoint);

    for (size_t i = 0, n = clusterSeeds.size(); i < n; ++i) {
        std::vector<int> clusterNeighors =
            calculate_cluster(points.at(clusterSeeds[i]));
        if (clusterNeighors.size() >= min_sample) {
            std::vector<int>::iterator iterNeighors;
            for (iterNeighors = clusterNeighors.begin();
                 iterNeighors != clusterNeighors.end(); ++iterNeighors) {
                if (points.at(*iterNeighors).cluster_id == UNCLASSIFIED ||
                    points.at(*iterNeighors).cluster_id == NOISE) {
                    if (points.at(*iterNeighors).cluster_id == UNCLASSIFIED) {
                        clusterSeeds.push_back(*iterNeighors);
                        n = clusterSeeds.size();
                    }
                    points.at(*iterNeighors).cluster_id = cluster_id;
                }
            }
        }
    }

    return SUCCESS;
}

std::vector<int> DBScan::calculate_cluster(point& p) {
    int idx = 0;
    std::vector<point>::iterator iter;
    std::vector<int> clusterIndex;
    for (iter = points.begin(); iter != points.end(); ++iter) {
        if (calculate_distance(p, *iter) <= eps) {
            clusterIndex.push_back(idx);
        }
        idx++;
    }
    return clusterIndex;
}

inline float DBScan::calculate_distance(const point& p1, const point& p2) {
    float dist = 0;
    for (size_t i = 0; i < std::min((*X)[p1.i].size(), (*X)[p2.i].size());
         ++i) {
        dist += pow((*X)[p1.i][i] - (*X)[p2.i][i], 2);
    }
    return sqrt(dist);
}

inline float DBScan::calculate_distance(const std::vector<float>& p1,
                                        const point& p2) {
    float dist = 0;
    for (size_t i = 0; i < std::min(p1.size(), (*X)[p2.i].size()); ++i) {
        dist += pow(p1[i] - (*X)[p2.i][i], 2);
    }
    return sqrt(dist);
}

bool DBScan::points_equal(const point& p1, const point& p2) {
    bool flag = (*X)[p1.i].size() == (*X)[p2.i].size();
    for (size_t i = 0; i < (*X)[p1.i].size(); ++i) {
        flag = flag and (abs((*X)[p1.i][i] - (*X)[p2.i][i]) <= 0.0001);
    }
    return flag;
}

std::vector<int> DBScan::predict() {
    assert(X);
    std::vector<int> labels;
    for (auto p : points) {
        labels.push_back(p.cluster_id);
    }
    return labels;
}

std::vector<int> DBScan::create_predictions(const int user_cluster_id) {
    std::vector<int> users_same_cluster;
    std::vector<point>::iterator iter;
    for (iter = points.begin(); iter != points.end(); ++iter) {
        if (iter->cluster_id == user_cluster_id) {
            users_same_cluster.push_back(iter->user_id);
        }
    }
    return users_same_cluster;
}

std::vector<int> DBScan::predict(const int user_id) {
    assert(X);
    auto user_i = std::find(std::begin(users_id), std::end(users_id), user_id);
    int i = std::distance(users_id.begin(), user_i);

    int user_cluster_id = points[i].cluster_id;

    return create_predictions(user_cluster_id);
}

std::vector<int> DBScan::predict(const std::vector<float>& user_values) {
    assert(X);
    std::vector<float> dists;
    std::vector<point>::iterator iter;
    for (iter = points.begin(); iter != points.end(); ++iter) {
        dists.push_back(calculate_distance(user_values, *iter));
    }

    size_t K = min_sample;
    std::vector<int> cluster_ids(K);

    for (size_t k = 0; k < K; ++k) {
        auto result = std::min_element(dists.begin(), dists.end());
        int result_i = std::distance(dists.begin(), result);
        cluster_ids[k] = points[result_i].cluster_id;
        *result = std::numeric_limits<float>::max();
    }

    std::map<int, int> counters;
    for (auto i : cluster_ids) {
        ++counters[i];
    }

    auto key_of_max_value = std::max_element(
        counters.begin(), counters.end(),
        [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
            return p1.second < p2.second;
        });

    int user_cluster_id = key_of_max_value->first;

    return create_predictions(user_cluster_id);
}
