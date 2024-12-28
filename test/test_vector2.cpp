#include <math/Vector2.hpp>

#include <gtest/gtest.h>

using namespace cam::math;

TEST(Vector2Test, DefaultInitialization) {
    Vector2 v;
    EXPECT_EQ(v, Vector2::kZERO);
}

TEST(Vector2Test, ScalarInitialization) {
    Vector2 v(5);
    EXPECT_EQ(v, Vector2(5, 5));
}

TEST(Vector2Test, ComponentInitialization) {
    Vector2 v(3, 7);
    EXPECT_EQ(v, Vector2(3, 7));
}

TEST(Vector2Test, SetMethods) {
    Vector2 v;
    v.Set(5);
    EXPECT_EQ(v, Vector2(5, 5));
    v.Set(2, 8);
    EXPECT_EQ(v, Vector2(2, 8));
    Vector2 v2(4, 4);
    v.Set(v2);
    EXPECT_EQ(v, v2);
}

TEST(Vector2Test, IsEqualWithEpsilon) {
    Vector2 v1(1.000001, 2.000001);
    Vector2 v2(1.000002, 2.000002);
    EXPECT_TRUE(v1.IsEqual(v2, 0.00001));
    EXPECT_FALSE(v1.IsEqual(v2, 0.0000001));
    EXPECT_TRUE(v1.IsNotEqual(v2, 0.0000001));
}

TEST(Vector2Test, EqualityOperators) {
    Vector2 v1(3, 4);
    Vector2 v2(3, 4);
    Vector2 v3(4, 5);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v1 == v3);
    EXPECT_TRUE(v1 != v3);
}

TEST(Vector2Test, ComparisonOperators) {
    Vector2 v1(1, 2);
    Vector2 v2(2, 3);
    Vector2 v3(0, 1);

    EXPECT_TRUE(v1 < v2);
    EXPECT_FALSE(v2 < v1);
    EXPECT_TRUE(v2 > v1);
    EXPECT_FALSE(v1 > v2);
    EXPECT_FALSE(v1 < v3);
    EXPECT_TRUE(v1 > v3);
}

TEST(Vector2Test, UnaryOperators) {
    Vector2 v(3, 4);
    EXPECT_EQ(+v, Vector2(3, 4));
    EXPECT_EQ(-v, Vector2(-3, -4));
}

TEST(Vector2Test, PlusEqualsOperators) {
    Vector2 v(1, 2);
    v += 3;
    EXPECT_EQ(v, Vector2(4, 5));

    v += Vector2(1, 1);
    EXPECT_EQ(v, Vector2(5, 6));
}

TEST(Vector2Test, MinusEqualsOperators) {
    Vector2 v(10, 20);
    v -= 5;
    EXPECT_EQ(v, Vector2(5, 15));

    v -= Vector2(2, 3);
    EXPECT_EQ(v, Vector2(3, 12));
}

TEST(Vector2Test, TimesEqualsOperators) {
    Vector2 v(2, 3);
    v *= 4;
    EXPECT_EQ(v, Vector2(8, 12));

    v *= Vector2(0.5, 2);
    EXPECT_EQ(v, Vector2(4, 24));
}

TEST(Vector2Test, DivideEqualsOperators) {
    Vector2 v(8, 16);
    v /= 4;
    EXPECT_EQ(v, Vector2(2, 4));

    v /= Vector2(2, 2);
    EXPECT_EQ(v, Vector2(1, 2));

    v /= 0;
    EXPECT_EQ(v, Vector2(1, 2));

    v /= Vector2(0, 3);
    EXPECT_EQ(v, Vector2(1, 2));
}


TEST(Vector2Test, AdditionOperators) {
    Vector2 v1(1, 2);
    Vector2 v2(3, 4);
    EXPECT_EQ(v1 + v2, Vector2(4, 6));
    EXPECT_EQ(v1 + 1, Vector2(2, 3));
    EXPECT_EQ(1 + v1, Vector2(2, 3));
}

TEST(Vector2Test, SubtractionOperators) {
    Vector2 v1(5, 6);
    Vector2 v2(3, 4);
    EXPECT_EQ(v1 - v2, Vector2(2, 2));
    EXPECT_EQ(v1 - 2, Vector2(3, 4));
    EXPECT_EQ(7 - v1, Vector2(2, 1));
}

TEST(Vector2Test, MultiplicationOperators) {
    Vector2 v1(2, 3);
    Vector2 v2(4, 5);
    EXPECT_EQ(v1 * v2, Vector2(8, 15));
    EXPECT_EQ(v1 * 2, Vector2(4, 6));
    EXPECT_EQ(3 * v1, Vector2(6, 9));
}

TEST(Vector2Test, DivisionOperators) {
    Vector2 v1(6, 9);
    Vector2 v2(3, 3);
    EXPECT_EQ(v1 / v2, Vector2(2, 3));
    EXPECT_EQ(v1 / 3, Vector2(2, 3));
    EXPECT_EQ(18 / v1, Vector2(3, 2));

    Vector2 v3(5, 5);
    Vector2 v4(0, 2);
    EXPECT_EQ(18 / v4, Vector2(18));
    EXPECT_EQ(v3 / v4, v3);
    EXPECT_EQ(v3 / 0, v3);
}

TEST(Vector2Test, MixedTypeOperations) {
    Vector2 v1(3.5, 4.5);
    EXPECT_EQ(v1 + 2, Vector2(5.5, 6.5));
    EXPECT_EQ(v1 - 1.5, Vector2(2, 3));
    EXPECT_EQ(v1 * 2, Vector2(7, 9));
    EXPECT_EQ(v1 / 2.0, Vector2(1.75, 2.25));

    Vector2 v2(1, 2);
    EXPECT_EQ(v2 + 3.5, Vector2(4.5, 5.5));
    EXPECT_EQ(1.0 / v2, Vector2(1, 0.5));
}
