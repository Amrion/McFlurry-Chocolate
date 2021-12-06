#pragma once

#include <bits/stdc++.h>

#define UNCLASSIFIED -1
#define SUCCESS 0
#define NOISE -2
#define FAILURE -3

struct point {
    int user_id;
    size_t i;
    int cluster_id;

    point();
    point(int _user_id, size_t _i, int _cluster_id=UNCLASSIFIED);
    ~point() = default;
};

class DBScan {
private:
    float eps;
    size_t min_sample;
    std::vector<int> users_id;
    std::vector<point> points;
    std::vector<std::vector<float>> *X;

    inline float calculateDistance(const point& p1, const point& p2);
    inline float calculateDistance(const std::vector<float>& p1, const point& p2);
    std::vector<int> calculateCluster(point& p);
    int expandCluster(point& p, int cluster_id);
    bool pointsEqual(const point& p1, const point& p2);

    std::vector<int> create_predictions(const int user_cluster_id);
public:
    DBScan(float _eps=2.5, 
    size_t _min_sample=4,
    std::vector<int> _users_id=std::vector<int>(0));
    ~DBScan();

    void fit(std::vector<std::vector<float>> *_X);  
    std::vector<int> predict();
    std::vector<int> predict(const int user_id);
    std::vector<int> predict(const std::vector<float>& user_values);
};
