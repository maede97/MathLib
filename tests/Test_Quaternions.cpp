#include <gtest/gtest.h>
#include <mathlib/quaternion.h>

TEST(Quaternion, Type) {
    EXPECT_EQ(typeid(Quaterniond::type), typeid(double));
    EXPECT_EQ(typeid(Quaternionf::type), typeid(float));
}

TEST(Quaternion, Size) {
    EXPECT_EQ(Quaterniond::size(), 4);
    EXPECT_EQ(Quaternionf::size(), 4);
}

TEST(Quaternion, Constructor) {
    Quaterniond q(1., 2., 3., 4.);
    EXPECT_DOUBLE_EQ(q.x(), 1.);
    EXPECT_DOUBLE_EQ(q.y(), 2.);
    EXPECT_DOUBLE_EQ(q.z(), 3.);
    EXPECT_DOUBLE_EQ(q.w(), 4.);

    Quaterniond q2 = Quaterniond::Identity();
    EXPECT_DOUBLE_EQ(q2.x(), 0.);
    EXPECT_DOUBLE_EQ(q2.y(), 0.);
    EXPECT_DOUBLE_EQ(q2.z(), 0.);
    EXPECT_DOUBLE_EQ(q2.w(), 1.);

    Quaterniond q3(Vector<3, double>(1., 2., 3.), 4.);
    EXPECT_DOUBLE_EQ(q3.x(), 0.24301995956120354);
    EXPECT_DOUBLE_EQ(q3.y(), 0.48603991912240707);
    EXPECT_DOUBLE_EQ(q3.z(), 0.72905987868361066);
    EXPECT_DOUBLE_EQ(q3.w(), -0.41614683654714241);

    Quaterniond q4;
    EXPECT_DOUBLE_EQ(q4.x(), 0.);
    EXPECT_DOUBLE_EQ(q4.y(), 0.);
    EXPECT_DOUBLE_EQ(q4.z(), 0.);
    EXPECT_DOUBLE_EQ(q4.w(), 0.);
}

TEST(Quaternion, QuaternionMultiplication) {
    Quaterniond q1(1., 2., 3., 4.);
    Quaterniond q2(2., 3., 4., 5.);

    Quaterniond q3 = q1 * q1;
    Quaterniond q4 = q1 * q2;
    Quaterniond q5 = q2 * q1;

    EXPECT_DOUBLE_EQ(q3.x(), 8.);
    EXPECT_DOUBLE_EQ(q3.y(), 16.);
    EXPECT_DOUBLE_EQ(q3.z(), 24.);
    EXPECT_DOUBLE_EQ(q3.w(), 2.);

    EXPECT_DOUBLE_EQ(q4.x(), 12.);
    EXPECT_DOUBLE_EQ(q4.y(), 24.);
    EXPECT_DOUBLE_EQ(q4.z(), 30.);
    EXPECT_DOUBLE_EQ(q4.w(), 0.);

    EXPECT_DOUBLE_EQ(q5.x(), 14.);
    EXPECT_DOUBLE_EQ(q5.y(), 20.);
    EXPECT_DOUBLE_EQ(q5.z(), 32.);
    EXPECT_DOUBLE_EQ(q5.w(), 0.);
}

TEST(Quaternion, VectorMultiplication) {
    Quaterniond q1(Vector<3, double>(5., 3., 1.), 4.);
    q1.normalize();

    Vector<3, double> v(1., 2., 3.);

    Vector<3, double> r = q1 * v;

    EXPECT_DOUBLE_EQ(r.x(), 1.7581828324054964);
    EXPECT_DOUBLE_EQ(r.y(), 2.4680066802253409);
    EXPECT_DOUBLE_EQ(r.z(), -2.1949342027035064);
}

TEST(Quaternion, Inverse) {
    Quaterniond q1(Vector<3, double>(5., 3., 1.), 4.);
    Quaterniond i = q1.inverse();

    EXPECT_EQ(Quaterniond::Identity(), q1 * i);
    EXPECT_EQ(Quaterniond::Identity(), i * q1);
}

TEST(Quaternion, Access) {
    Quaterniond q1(1., 2., 3., 4.);
    Quaterniond q2(Vector<3, double>(1., 0., 0.), 4.);

    EXPECT_DOUBLE_EQ(q1.w(), 4.);
    q1.w() = 5.;
    EXPECT_DOUBLE_EQ(q1.w(), 5.);
    EXPECT_EQ(q1.vec(), (Vector<3, double>(1., 2., 3.)));
    q1.setVec(Vector<3, double>(2., 3., 4.));
    EXPECT_EQ(q1.vec(), (Vector<3, double>(2., 3., 4.)));

    EXPECT_DOUBLE_EQ(q2.angle(), 4.);
    EXPECT_EQ(q2.axis(), (Vector<3, double>(1., 0., 0.)));
}