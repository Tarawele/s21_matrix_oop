#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(SumMatrix, True) {
    S21Matrix matrix_a(2, 2);
    S21Matrix matrix_b(2, 2);
    S21Matrix result(2, 2);

    matrix_a(0, 0) = 3.14;
    matrix_a(0, 1) = 0.56;
    matrix_a(1, 0) = -69.3;
    matrix_a(1, 1) = 0;

    matrix_b(0, 0) = -78.14;
    matrix_b(0, 1) = 0;
    matrix_b(1, 0) = -0.3;
    matrix_b(1, 1) = 2;

    result(0, 0) = -75;
    result(0, 1) = 0.56;
    result(1, 0) = -69.6;
    result(1, 1) = 2;
    matrix_a.SumMatrix(matrix_b);
    ASSERT_TRUE(matrix_a == result);
}
TEST(SumMatrix, False) {
    S21Matrix matrix_a(1, 2);
    S21Matrix matrix_b(2, 2);
    
    matrix_a(0, 0) = 3.14;
    matrix_a(0, 1) = 0.56;
    matrix_b(0, 0) = -78.14;
    matrix_b(0, 1) = 0;
    matrix_b(1, 0) = -0.3;
    matrix_b(1, 1) = 2;

    EXPECT_THROW(matrix_a.SumMatrix(matrix_b), out_of_range);
}
// TEST(SubMatrix, True) {
//     S21Matrix matrix_a(2, 2);
//     S21Matrix matrix_b(2, 2);
//     S21Matrix result(2, 2);

//     matrix_a(0, 0) = 3;
//     matrix_a(0, 1) = 2;
//     matrix_a(1, 0) = -6;
//     matrix_a(1, 1) = 0;

//     matrix_b(0, 0) = -7;
//     matrix_b(0, 1) = 0;
//     matrix_b(1, 0) = -3;
//     matrix_b(1, 1) = 2;

//     result(0, 0) = 10;
//     result(0, 1) = 2;
//     result(1, 0) = -3;
//     result(1, 1) = -2;

//     matrix_a.SubMatrix(matrix_b);
//     ASSERT_TRUE(matrix_a == result);
// }
// TEST(SubMatrix, False) {
//     S21Matrix matrix_a(1, 2);
//     S21Matrix matrix_b(2, 2);

//     matrix_a(0, 0) = 3;
//     matrix_a(0, 1) = 2;
//     matrix_b(0, 0) = -7;
//     matrix_b(0, 1) = 0;
//     matrix_b(1, 0) = -3;
//     matrix_b(1, 1) = 2;

//     EXPECT_THROW(matrix_a.SubMatrix(matrix_b), std::out_of_range);
// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}