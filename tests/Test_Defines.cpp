#include <gtest/gtest.h>
#include <mathlib/defines.h>

TEST(Defines, Size) {
    EXPECT_EQ(Vector1d::size(), 1);
    EXPECT_EQ(Vector2d::size(), 2);
    EXPECT_EQ(Vector3d::size(), 3);

    EXPECT_EQ(Vector1f::size(), 1);
    EXPECT_EQ(Vector2f::size(), 2);
    EXPECT_EQ(Vector3f::size(), 3);

    EXPECT_EQ(Vector1i::size(), 1);
    EXPECT_EQ(Vector2i::size(), 2);
    EXPECT_EQ(Vector3i::size(), 3);

    EXPECT_EQ(Vector1u::size(), 1);
    EXPECT_EQ(Vector2u::size(), 2);
    EXPECT_EQ(Vector3u::size(), 3);

    EXPECT_EQ((Vector<10, double>::size()), 10);
    EXPECT_EQ((Vector<10, float>::size()), 10);
    EXPECT_EQ((Vector<10, int>::size()), 10);
    EXPECT_EQ((Vector<10, unsigned>::size()), 10);
}

TEST(Defines, Type) {
    EXPECT_EQ(typeid(Vector1d::type), typeid(double));
    EXPECT_EQ(typeid(Vector2d::type), typeid(double));
    EXPECT_EQ(typeid(Vector3d::type), typeid(double));

    EXPECT_EQ(typeid(Vector1f::type), typeid(float));
    EXPECT_EQ(typeid(Vector2f::type), typeid(float));
    EXPECT_EQ(typeid(Vector3f::type), typeid(float));

    EXPECT_EQ(typeid(Vector1i::type), typeid(int));
    EXPECT_EQ(typeid(Vector2i::type), typeid(int));
    EXPECT_EQ(typeid(Vector3i::type), typeid(int));

    EXPECT_EQ(typeid(Vector1u::type), typeid(unsigned));
    EXPECT_EQ(typeid(Vector2u::type), typeid(unsigned));
    EXPECT_EQ(typeid(Vector3u::type), typeid(unsigned));

    EXPECT_EQ(typeid(Vector<10, double>::type), typeid(double));
    EXPECT_EQ(typeid(Vector<10, float>::type), typeid(float));
    EXPECT_EQ(typeid(Vector<10, int>::type), typeid(int));
    EXPECT_EQ(typeid(Vector<10, unsigned>::type), typeid(unsigned));
}