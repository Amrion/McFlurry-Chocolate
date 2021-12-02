#include "gtest/gtest.h"

#include "recsys.hpp"

TEST(ALS_CHECK, FRABENIUS_NORM) {
    ALS model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    matrix<float> B(10, 10); model.random_init(B, 0, 10);
    matrix<float> AB = prod(A, B);

    EXPECT_FLOAT_EQ(model.frabenius_norm(AB, A, B), 0);
}

TEST(ALS_CHECK, EUCLIDEAN_NORM) {
    ALS model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
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

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    matrix<float> W(10, 3); model.random_init(W, 0, 10);
    matrix<float> H(3, 10); model.random_init(H, 0, 10);

    model.gradient_descent(A, W, H);
    EXPECT_TRUE(model.frabenius_norm(A, W, H) < 20);
}

TEST(ALS_CHECK, GRADIENT_DESCENT_REG) {
    ALS model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    matrix<float> W(10, 3); model.random_init(W, 0, 10);
    matrix<float> H(3, 10); model.random_init(H, 0, 10);

    model.gradient_descent_reg(A, W, H);
    EXPECT_TRUE(model.frabenius_norm(A, W, H) < 20);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
