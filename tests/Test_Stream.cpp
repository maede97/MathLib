#include <gtest/gtest.h>
#include <mathlib/vector.h>

#include <sstream>

TEST(Stream, Print) {
    Vector<3, double> v = Vector<3, double>({1., 2., 3.});
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), std::string("1 2 3"));

    Vector<3, double> v2 = Vector<3, double>({1.5, 2.25, 3.75});
    std::stringstream ss2;
    ss2 << v2;
    EXPECT_EQ(ss2.str(), std::string("1.5 2.25 3.75"));
}

TEST(Stream, Read) {
    Vector<3, double> v;
    EXPECT_DOUBLE_EQ(v.squaredNorm(), 0.);
    std::stringstream ss("1 2 3");
    ss >> v;
    EXPECT_DOUBLE_EQ(v.squaredNorm(), 14.0);
}