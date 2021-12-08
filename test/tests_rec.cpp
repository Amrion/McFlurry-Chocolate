#include "gtest/gtest.h"
#include "recsys.hpp"

TEST(ALS_CHECK, FRABENIUS_NORM) {
    ALS model;

    matrix<float> A(10, 10);
    model.random_init(A, 0, 10);
    matrix<float> B(10, 10);
    model.random_init(B, 0, 10);
    matrix<float> AB = prod(A, B);

    EXPECT_FLOAT_EQ(model.frabenius_norm(AB, A, B), 0);
}

TEST(ALS_CHECK, EUCLIDEAN_NORM) {
    ALS model;

    matrix<float> A(10, 10);
    model.random_init(A, 0, 10);
    float sum = 0;
    for (size_t i = 0; i < A.size1(); ++i) {
        for (size_t j = 0; j < A.size2(); ++j) {
            sum += pow(A(i, j), 2);
        }
    }

    EXPECT_FLOAT_EQ(model.euclidean_norm(A), 0.5 * sqrt(sum));
}

TEST(ALS_CHECK, GRADIENT_DESCENT) {
    ALS model;

    matrix<float> A(10, 10);
    model.random_init(A, 0, 10);
    matrix<float> W(10, 3);
    model.random_init(W, 0, 10);
    matrix<float> H(3, 10);
    model.random_init(H, 0, 10);

    model.gradient_descent(A, W, H);
    EXPECT_TRUE(model.frabenius_norm(A, W, H) < 20);
}

TEST(ALS_CHECK, GRADIENT_DESCENT_REG) {
    ALS model;

    matrix<float> A(10, 10);
    model.random_init(A, 0, 10);
    matrix<float> W(10, 3);
    model.random_init(W, 0, 10);
    matrix<float> H(3, 10);
    model.random_init(H, 0, 10);

    model.gradient_descent_reg(A, W, H);
    EXPECT_TRUE(model.frabenius_norm(A, W, H) < 20);
}

void generate_circle(std::vector<std::vector<float>>& X, const float radius,
                     const float m_x_center, const float m_y_center,
                     const size_t NUM_IN_EACH_CLUSTER) {
    srand(time(NULL));
    for (size_t i = 0; i < NUM_IN_EACH_CLUSTER; ++i) {
        float ran1 = static_cast<float>(rand() / RAND_MAX);
        float angle = ran1 * 2 * M_PI;

        X.push_back({m_x_center + static_cast<float>(radius * sin(angle)),
                     m_y_center + static_cast<float>(radius * cos(angle))});
    }
}

TEST(DBSCAN_CHECK, TWO_CIRCLES) {
    // generate Data for clustering!
    std::vector<int> labels;
    const size_t NUM_IN_EACH_CLUSTER = 1000;
    std::vector<std::vector<float>> X;

    generate_circle(X, 10, 0, 0, NUM_IN_EACH_CLUSTER);
    generate_circle(X, 3, 0, 0, NUM_IN_EACH_CLUSTER);

    for (size_t i = 0; i < NUM_IN_EACH_CLUSTER; ++i) {
        labels.push_back(1);
    }

    for (size_t i = 0; i < NUM_IN_EACH_CLUSTER; ++i) {
        labels.push_back(2);
    }

    DBScan model;
    model.fit(&X);
    std::vector<int> ans = model.predict();

    for (size_t i = 0; i < labels.size(); ++i) {
        EXPECT_EQ(ans[i], labels[i]);
    }
}

TEST(DBSCAN_CHECK, TWO_CIRCLES_WITH_USER) {
    const size_t NUM_IN_EACH_CLUSTER = 1000;
    std::vector<std::vector<float>> X;

    generate_circle(X, 10, 0, 0, NUM_IN_EACH_CLUSTER);
    generate_circle(X, 3, 0, 0, NUM_IN_EACH_CLUSTER);

    DBScan model;
    model.fit(&X);
    std::vector<int> ans = model.predict(0);

    for (size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i], i);
    }
}

TEST(DBSCAN_CHECK, TWO_CIRCLES_BY_VALUES) {
    // generate Data for clustering!
    const size_t NUM_IN_EACH_CLUSTER = 1000;
    std::vector<std::vector<float>> X;

    generate_circle(X, 10, 0, 0, NUM_IN_EACH_CLUSTER);
    generate_circle(X, 3, 0, 0, NUM_IN_EACH_CLUSTER);

    DBScan model;
    model.fit(&X);
    std::vector<float> user_values = {0., 0.};
    std::vector<int> ans = model.predict(user_values);

    for (size_t i = 0; i < ans.size(); ++i) {
        EXPECT_EQ(ans[i], i + NUM_IN_EACH_CLUSTER);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}