#include "gtest/gtest.h"

#include "recsys.hpp"

TEST(MATRIX_CHECK, CONSTRUCTOR_N_M) {
    matrix<int> B(10, 10);
    for (size_t i = 0; i < B.size_n(); ++i) {
        for (size_t j = 0; j < B.size_m(); ++j) {
            EXPECT_EQ(B[i][j], 0);
        }
    }
}

TEST(MATRIX_CHECK, CONSTRUCTOR_VECTOR) {
    vector<vector<int>> Vi(10, vector<int>(10));
    for (size_t i = 0; i < Vi.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vi[i][j] = i + j;
        }
    }

    matrix<int> B(Vi);
    for (size_t i = 0; i < B.size_n(); ++i) {
        for (size_t j = 0; j < B.size_m(); ++j) {
            EXPECT_EQ(B[i][j], Vi[i][j]);
        }
    }
}

TEST(MATRIX_CHECK, MULTIPLIE_MATRIX) {
    vector<vector<int>> Vi(10, vector<int>(10));
    for (size_t i = 0; i < Vi.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vi[i][j] = i + j;
        }
    }
    vector<vector<int>> Vii(10, vector<int>(10));
    for (size_t i = 0; i < Vii.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vii[i][j] = i - j;
        }
    }
    vector<vector<int>> ANS(10, vector<int>(10));
    for (size_t i = 0; i < ANS.size(); ++i) {
        for (size_t j = 0; j < ANS[i].size(); ++j) {
            for (size_t k = 0; k < ANS[i].size(); ++k) {
                ANS[i][j] += Vi[i][k] * Vii[k][j];
            }
        }
    }

    matrix<int> A(Vi);
    matrix<int> B(Vii);

    matrix<int> AB = A*B;
    for (size_t i = 0; i < AB.size_n(); ++i) {
        for (size_t j = 0; j < AB.size_m(); ++j) {
            EXPECT_EQ(AB[i][j], ANS[i][j]);
        }
    }
}

TEST(MATRIX_CHECK, MULTIPLIE_NUMBER) {
    vector<vector<int>> Vi(10, vector<int>(10));
    for (size_t i = 0; i < Vi.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vi[i][j] = i + j;
        }
    }
    matrix<int> A(Vi);
    A = A * 5;
    for (size_t i = 0; i < A.size_n(); ++i) {
        for (size_t j = 0; j < A.size_m(); ++j) {
            EXPECT_EQ(A[i][j], Vi[i][j] * 5);
        }
    }
}

TEST(MATRIX_CHECK, SUM_MATRIX) {
    vector<vector<int>> Vi(10, vector<int>(10));
    for (size_t i = 0; i < Vi.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vi[i][j] = i + j;
        }
    }
    vector<vector<int>> Vii(10, vector<int>(10));
    for (size_t i = 0; i < Vii.size(); ++i) {
        for (size_t j = 0; j < Vi[i].size(); ++j) {
            Vii[i][j] = i - j;
        }
    }

    matrix<int> A(Vi);
    matrix<int> B(Vii);

    matrix<int> AB = A + B;
    for (size_t i = 0; i < AB.size_n(); ++i) {
        for (size_t j = 0; j < AB.size_m(); ++j) {
            EXPECT_EQ(AB[i][j], Vi[i][j] + Vii[i][j]);
        }
    }
}

TEST(NMF_CHECK, FRABENIUS_NORM) {
    matrix<float> A(10, 10); A.random_init(0, 10);
    matrix<float> B(10, 10); B.random_init(0, 10);
    matrix<float> AB = A * B;

    NMF model;
    EXPECT_FLOAT_EQ(model.Frabenius_norm(AB, A, B), 0);
}

TEST(NMF_CHECK, EUCLIDEAN_NORM) {
    matrix<float> A(10, 10); A.random_init(0, 10);
    float sum = 0;
    for (size_t i = 0; i < A.size_n(); ++i) {
        for (size_t j = 0; j < A.size_m(); ++j) {
            sum += pow(A[i][j], 2);
        }
    }

    NMF model;
    EXPECT_FLOAT_EQ(model.Euclidean_norm(A), 0.5 * sqrt(sum));
}

TEST(NMF_CHECK, GRADIENT_DESCENT) {
    matrix<float> A(10, 10); A.random_init(0, 10);
    matrix<float> W(10, 3); A.random_init(0, 10);
    matrix<float> H(10, 3); A.random_init(0, 10);

    NMF model;
    model.gradient_descent(A, W, H);
    EXPECT_EQ(model.Frabenius_norm(A, W, H) < 0.01, true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
