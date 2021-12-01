#include "gtest/gtest.h"

#include "recsys.hpp"

TEST(NMF_CHECK, FRABENIUS_NORM) {
    NMF model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    matrix<float> B(10, 10); model.random_init(B, 0, 10);
    matrix<float> AB = prod(A, B);

    EXPECT_FLOAT_EQ(model.Frabenius_norm(AB, A, B), 0);
}

TEST(NMF_CHECK, EUCLIDEAN_NORM) {
    NMF model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    float sum = 0;
    for (size_t i = 0; i < A.size1(); ++i) {
        for (size_t j = 0; j < A.size2(); ++j) {
            sum += pow(A(i, j), 2);
        }
    }

    EXPECT_FLOAT_EQ(model.Euclidean_norm(A), 0.5 * sqrt(sum));
}

TEST(NMF_CHECK, GRADIENT_DESCENT) {
    NMF model;

    matrix<float> A(10, 10); model.random_init(A, 0, 10);
    matrix<float> W(10, 3); model.random_init(W, 0, 10);
    matrix<float> H(3, 10); model.random_init(H, 0, 10);

    model.gradient_descent(A, W, H);
    EXPECT_EQ(model.Frabenius_norm(A, W, H) < 10, true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
