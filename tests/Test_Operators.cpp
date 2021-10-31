#include <gtest/gtest.h>
#include <mathlib/defines.h>
#include <mathlib/operators.h>

TEST(Operators, Plus) {
    Vector3d v1 = Vector3d({1., 2., 3.});
    Vector3d v2 = Vector3d({4., 5., 6.});
    Vector3d sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum[0], 5.);
    EXPECT_DOUBLE_EQ(sum[1], 7.);
    EXPECT_DOUBLE_EQ(sum[2], 9.);
}

TEST(Operators, Minus) {
    Vector3d v1 = Vector3d({1., 2., 3.});
    Vector3d v2 = Vector3d({4., 5., 6.});
    Vector3d diff = v1 - v2;
    EXPECT_DOUBLE_EQ(diff[0], -3.);
    EXPECT_DOUBLE_EQ(diff[1], -3.);
    EXPECT_DOUBLE_EQ(diff[2], -3.);
}

TEST(Operators, Product) {
    Vector3d v1 = Vector3d({1., 2., 3.});
    Vector3d v2 = Vector3d({4., 5., 6.});
    Vector3d product = v1 * v2;
    EXPECT_DOUBLE_EQ(product[0], 4.);
    EXPECT_DOUBLE_EQ(product[1], 10.);
    EXPECT_DOUBLE_EQ(product[2], 18.);
}

TEST(Operators, Division) {
    Vector3d v1 = Vector3d({1., 2., 3.});
    Vector3d v2 = Vector3d({4., 5., 6.});
    Vector3d div = v1 / v2;
    EXPECT_DOUBLE_EQ(div[0], 0.25);
    EXPECT_DOUBLE_EQ(div[1], 0.4);
    EXPECT_DOUBLE_EQ(div[2], 0.5);
}

TEST(Operators, Equality) {
    Vector3d v1({1., 2., 3.});
    Vector3d v2({1., 2., 3.});
    EXPECT_EQ(v1, v2);
}

TEST(Operators, Inequality) {
    Vector3d v1({1., 2., 3.});
    Vector3d v2({1.001, 2., 3.});
    EXPECT_NE(v1, v2);
}