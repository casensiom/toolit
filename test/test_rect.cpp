#include <math/Rect.hpp>
#include <math/Vector2.hpp>

#include <gtest/gtest.h>

using namespace cam::math;

TEST(RectBaseTest, DefaultConstructor) {
    Rectf rect;
    EXPECT_EQ(rect.getPos(), Vector2f(0.0f, 0.0f));
    EXPECT_EQ(rect.getSize(), Vector2f(0.0f, 0.0f));
    EXPECT_EQ(rect.area(), 0.0f);
}

TEST(RectBaseTest, ParameterizedConstructor) {
    Rect rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(rect.getPos(), Vector2(1.0, 2.0));
    EXPECT_EQ(rect.getSize(), Vector2(3.0, 4.0));
    EXPECT_EQ(rect.getWidth(), 3.0);
    EXPECT_EQ(rect.getHeight(), 4.0);
    EXPECT_EQ(rect.tl(), Vector2(1.0, 2.0));
    EXPECT_EQ(rect.tr(), Vector2(4.0, 2.0));
    EXPECT_EQ(rect.br(), Vector2(4.0, 6.0));
    EXPECT_EQ(rect.bl(), Vector2(1.0, 6.0));
    EXPECT_EQ(rect.area(), 12.0);
}

TEST(RectBaseTest, AreaCalculation) {
    Recti rect(0, 0, 10, 5);
    EXPECT_EQ(rect.area(), 50);

    Recti rectZero(0, 0, 0, 0);
    EXPECT_EQ(rectZero.area(), 0);

    Recti rectNegativeSize(0, 0, -10, -5);
    EXPECT_EQ(rectNegativeSize.area(), 50);
}

TEST(RectBaseTest, WrapPoints) {
    std::vector<Vector2f> points = {Vector2f(1.0f, 2.0f), Vector2f(3.0f, 4.0f), Vector2f(0.0f, 5.0f), Vector2f(2.0f, 1.0f)};

    Rectf rect = Rectf::wrap(points);

    EXPECT_EQ(rect.tl(), Vector2f(0.0f, 1.0f));
    EXPECT_EQ(rect.br(), Vector2f(3.0f, 5.0f));
    EXPECT_EQ(rect.area(), 12.0f);
}

TEST(RectBaseTest, WrapPointsEmpty) {
    std::vector<Vector2f> points;

    Rectf rect = Rectf::wrap(points);

    EXPECT_EQ(rect.tl(), Vector2f(0, 0));
    EXPECT_EQ(rect.br(), Vector2f(0, 0));
    EXPECT_EQ(rect.area(), 0);
}

TEST(RectBaseTest, BoundsWithSinglePoint) {
    std::vector<Vector2> points = {Vector2(5.0, 7.0)};

    Rect rect = Rect::wrap(points);

    EXPECT_EQ(rect.tl(), Vector2(5.0, 7.0));
    EXPECT_EQ(rect.br(), Vector2(5.0, 7.0));
    EXPECT_EQ(rect.area(), 0.0);
}

TEST(RectBaseTest, NegativeDimensions) {
    Recti rect(5, 5, -10, -10);

    EXPECT_EQ(rect.tl(), Vector2i(5, 5));
    EXPECT_EQ(rect.tr(), Vector2i(-5, 5));
    EXPECT_EQ(rect.bl(), Vector2i(5, -5));
    EXPECT_EQ(rect.br(), Vector2i(-5, -5));
    EXPECT_EQ(rect.area(), 100);
}

TEST(RectBaseTest, LargeValues) {
    Recti rect(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
               std::numeric_limits<int>::max());

    EXPECT_GT(rect.area(), 0);    // Area should be large but calculable without overflow.
}

TEST(RectBaseTest, WrapPointsWithNegativeCoordinates) {
    std::vector<Vector2i> points = {Vector2i(-5, -5), Vector2i(-10, -10), Vector2i(0, 0)};

    Recti rect = Recti::wrap(points);

    EXPECT_EQ(rect.tl(), Vector2i(-10, -10));
    EXPECT_EQ(rect.br(), Vector2i(0, 0));
    EXPECT_EQ(rect.area(), 100);
}
