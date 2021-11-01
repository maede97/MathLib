#include <gtest/gtest.h>
#include <mathlib/defines.h>
#include <mathlib/vector.h>

TEST(Vector, Type) {
    EXPECT_EQ(typeid(Vector<1, char>::type), typeid(char));
    EXPECT_EQ(typeid(Vector<1, unsigned long long>::type), typeid(unsigned long long));
}

TEST(Vector, Size) {
    EXPECT_EQ(Vector3d::size(), 3);
    EXPECT_EQ((Vector<12, double>::size()), 12);
    EXPECT_EQ((Vector<200, double>::size()), 200);
}

TEST(Vector, Constructor) {
    Vector3d v1;
    EXPECT_DOUBLE_EQ(v1.at(0), 0.);

    Vector3d v2(3.);
    EXPECT_DOUBLE_EQ(v2.at(0), 3.);

    Vector3d v3(std::vector({1., 2., 3.}));
    EXPECT_DOUBLE_EQ(v3.at(0), 1.);

    Vector3d v4 = v3;
    EXPECT_DOUBLE_EQ(v4.at(0), 1.);

    double data[3] = {1., 2., 3.};
    Vector3d v5(data);
    EXPECT_DOUBLE_EQ(v5.at(0), 1.);

    Vector2d v6(1., 2.);
    EXPECT_DOUBLE_EQ(v6.at(0), 1.);
    EXPECT_DOUBLE_EQ(v6.at(1), 2.);
}

TEST(Vector, Norm) {
    Vector3d v = Vector3d(1., 2., 3.);
    EXPECT_DOUBLE_EQ(v.norm(), std::sqrt(14.));

    Vector<6, double> v2 = Vector<6, double>({4., 7., 1., 7., 2., 7.});
    EXPECT_DOUBLE_EQ(v2.norm(), std::sqrt(168.));
}

TEST(Vector, SquaredNorm) {
    Vector3d v = Vector3d(1., 2., 3.);
    EXPECT_DOUBLE_EQ(v.squaredNorm(), 14.);

    Vector<6, double> v2 = Vector<6, double>({4., 7., 1., 7., 2., 7.});
    EXPECT_DOUBLE_EQ(v2.squaredNorm(), 168.);
}

TEST(Vector, Normalize) {
    Vector3d v1 = Vector3d(1., 0., 0.);
    v1.normalize();
    EXPECT_DOUBLE_EQ(v1[0], 1.);
    EXPECT_DOUBLE_EQ(v1[1], 0.);
    EXPECT_DOUBLE_EQ(v1[2], 0.);

    Vector3d v2 = Vector3d(42., 15., 0.24);
    v2.normalize();
    double norm_ = std::sqrt(1989.0576);
    EXPECT_DOUBLE_EQ(v2[0], 42. / norm_);
    EXPECT_DOUBLE_EQ(v2[1], 15. / norm_);
    EXPECT_DOUBLE_EQ(v2[2], 0.24 / norm_);
}

TEST(Vector, Normalized) {
    Vector3d v1 = Vector3d(1., 0., 0.);
    Vector3d v2 = v1.normalized();
    EXPECT_DOUBLE_EQ(v1[0], 1.);
    EXPECT_DOUBLE_EQ(v1[1], 0.);
    EXPECT_DOUBLE_EQ(v1[2], 0.);
    EXPECT_DOUBLE_EQ(v2[0], 1.);
    EXPECT_DOUBLE_EQ(v2[1], 0.);
    EXPECT_DOUBLE_EQ(v2[2], 0.);

    Vector3d v3 = Vector3d(42., 15., 0.24);
    Vector3d v4 = v3.normalized();
    double norm_ = std::sqrt(1989.0576);
    EXPECT_DOUBLE_EQ(v3[0], 42.);
    EXPECT_DOUBLE_EQ(v3[1], 15.);
    EXPECT_DOUBLE_EQ(v3[2], 0.24);
    EXPECT_DOUBLE_EQ(v4[0], 42. / norm_);
    EXPECT_DOUBLE_EQ(v4[1], 15. / norm_);
    EXPECT_DOUBLE_EQ(v4[2], 0.24 / norm_);
}

TEST(Vector, OperatorAccess) {
    Vector3d v1 = Vector3d(1., 0., 0.);
    EXPECT_DOUBLE_EQ(v1[0], 1.);
    EXPECT_DOUBLE_EQ(v1[1], 0.);
    EXPECT_DOUBLE_EQ(v1[2], 0.);
    v1[1] = 2.;
    EXPECT_DOUBLE_EQ(v1[0], 1.);
    EXPECT_DOUBLE_EQ(v1[1], 2.);
    EXPECT_DOUBLE_EQ(v1[2], 0.);

    Vector3d v2 = Vector3d(1., 0., 0.);
    EXPECT_DOUBLE_EQ(v2(0), 1.);
    EXPECT_DOUBLE_EQ(v2(1), 0.);
    EXPECT_DOUBLE_EQ(v2(2), 0.);
    v2(1) = 2.;
    EXPECT_DOUBLE_EQ(v2(0), 1.);
    EXPECT_DOUBLE_EQ(v2(1), 2.);
    EXPECT_DOUBLE_EQ(v2(2), 0.);

    EXPECT_DOUBLE_EQ(v2.x(), 1.);
    EXPECT_DOUBLE_EQ(v2.y(), 2.);
    EXPECT_DOUBLE_EQ(v2.z(), 0.);

    v2.z() = 3.;

    EXPECT_DOUBLE_EQ(v2.x(), 1.);
    EXPECT_DOUBLE_EQ(v2.y(), 2.);
    EXPECT_DOUBLE_EQ(v2.z(), 3.);
}

TEST(Vector, Sum) {
    Vector3d v = Vector3d(42., 15., 0.24);
    EXPECT_DOUBLE_EQ(v.sum(), 57.24);
}

TEST(Vector, Dot) {
    Vector3d v1 = Vector3d(1., 0., 0.);
    Vector3d v2 = Vector3d(0., 1., 0.);
    Vector3d v3 = Vector3d(5., 1., 6.);

    EXPECT_DOUBLE_EQ(v1.dot(v2), 0.);
    EXPECT_DOUBLE_EQ(v1.dot(v3), 5.);

    EXPECT_DOUBLE_EQ(v1.dot(v1), v1.squaredNorm());
    EXPECT_DOUBLE_EQ(v2.dot(v2), v2.squaredNorm());
    EXPECT_DOUBLE_EQ(v3.dot(v3), v3.squaredNorm());
}

TEST(Vector, Min) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    EXPECT_DOUBLE_EQ(v1.min(), 1.);

    Vector3d v2 = Vector3d(5., 1., -6.);
    EXPECT_DOUBLE_EQ(v2.min(), -6.);
}

TEST(Vector, Max) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    EXPECT_DOUBLE_EQ(v1.max(), 6.);

    Vector3d v2 = Vector3d(5., 1., -6.);
    EXPECT_DOUBLE_EQ(v2.max(), 5.);
}

TEST(Vector, MinCoeff) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    v1.minCoeff() = 3.;
    EXPECT_DOUBLE_EQ(v1.x(), 5.);
    EXPECT_DOUBLE_EQ(v1.y(), 3.);
    EXPECT_DOUBLE_EQ(v1.z(), 6.);
}

TEST(Vector, MaxCoeff) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    v1.maxCoeff() = 3.;
    EXPECT_DOUBLE_EQ(v1.x(), 5.);
    EXPECT_DOUBLE_EQ(v1.y(), 1.);
    EXPECT_DOUBLE_EQ(v1.z(), 3.);
}

TEST(Vector, OperatorWithVector) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    Vector3d v2 = Vector3d(4., 5., 6.);
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1[0], 9.);
    EXPECT_DOUBLE_EQ(v1[1], 6.);
    EXPECT_DOUBLE_EQ(v1[2], 12.);

    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1[0], 5.);
    EXPECT_DOUBLE_EQ(v1[1], 1.);
    EXPECT_DOUBLE_EQ(v1[2], 6.);

    v1 *= v2;
    EXPECT_DOUBLE_EQ(v1[0], 20.);
    EXPECT_DOUBLE_EQ(v1[1], 5.);
    EXPECT_DOUBLE_EQ(v1[2], 36.);

    v1 /= v2;
    EXPECT_DOUBLE_EQ(v1[0], 5.);
    EXPECT_DOUBLE_EQ(v1[1], 1.);
    EXPECT_DOUBLE_EQ(v1[2], 6.);
}

TEST(Vector, OperatorWithScalar) {
    Vector3d v1 = Vector3d(5., 1., 6.);
    double v2 = 3.;
    v1 += v2;
    EXPECT_DOUBLE_EQ(v1[0], 8.);
    EXPECT_DOUBLE_EQ(v1[1], 4.);
    EXPECT_DOUBLE_EQ(v1[2], 9.);

    v1 -= v2;
    EXPECT_DOUBLE_EQ(v1[0], 5.);
    EXPECT_DOUBLE_EQ(v1[1], 1.);
    EXPECT_DOUBLE_EQ(v1[2], 6.);

    v1 *= v2;
    EXPECT_DOUBLE_EQ(v1[0], 15.);
    EXPECT_DOUBLE_EQ(v1[1], 3.);
    EXPECT_DOUBLE_EQ(v1[2], 18.);

    v1 /= v2;
    EXPECT_DOUBLE_EQ(v1[0], 5.);
    EXPECT_DOUBLE_EQ(v1[1], 1.);
    EXPECT_DOUBLE_EQ(v1[2], 6.);
}

TEST(Vector, Head) {
    Vector<6, double> v({1., 2., 3., 4., 5., 6});
    Vector3d v2(1., 2., 3.);
    EXPECT_EQ(v.head<3>(), v2);
}

TEST(Vector, Tail) {
    Vector<6, double> v({1., 2., 3., 4., 5., 6});
    Vector3d v2(4., 5., 6.);
    EXPECT_EQ(v.tail<3>(), v2);
}

TEST(Vector, Segment) {
    Vector<6, double> v({1., 2., 3., 4., 5., 6});
    Vector3d v2(2., 3., 4.);
    EXPECT_EQ((v.segment<1, 3>()), v2);
}

TEST(Vector, CommaInit) {
    Vector3d v1;
    v1 << 1., 2., 3.;
    Vector3d v2(1., 2., 3.);
    EXPECT_EQ(v1, v2);

    // Throw if too many.
    EXPECT_THROW((v1 << 1., 2., 3., 4.), std::runtime_error);
}

TEST(Vector, Cast) {
    Vector3d v1(1.5, 2.5, 3.75);

    Vector3i casted = v1.cast<int>();
    EXPECT_EQ(casted.x(), 1);
    EXPECT_EQ(casted.y(), 2);
    EXPECT_EQ(casted.z(), 3);
}

TEST(Vector, Cross) {
    Vector3d v1(1.5, 2.5, 3.5);
    Vector3d v2(1., 1., 2.);

    Vector3d v3 = v1.cross(v2);
    Vector3d v4 = v2.cross(v1);
    Vector3d v5 = v3.cross(v4);

    EXPECT_DOUBLE_EQ(v3.x(), 1.5);
    EXPECT_DOUBLE_EQ(v3.y(), 0.5);
    EXPECT_DOUBLE_EQ(v3.z(), -1.);

    EXPECT_DOUBLE_EQ(v4.x(), -1.5);
    EXPECT_DOUBLE_EQ(v4.y(), -0.5);
    EXPECT_DOUBLE_EQ(v4.z(), 1.);

    EXPECT_DOUBLE_EQ(v5.x(), 0.);
    EXPECT_DOUBLE_EQ(v5.y(), 0.);
    EXPECT_DOUBLE_EQ(v5.z(), 0.);
}

TEST(Stream, ToString) {
    Vector<3, double> v = Vector<3, double>(1., 2., 3.);
    EXPECT_EQ(v.to_string(), std::string("1.000000 2.000000 3.000000"));

    Vector<3, double> v2 = Vector<3, double>(1.5, 2.25, 3.75);
    EXPECT_EQ(v2.to_string(), std::string("1.500000 2.250000 3.750000"));

    EXPECT_EQ(v2.cast<int>().to_string(), std::string("1 2 3"));
}