#include <pathfinder/PathFinder.hpp>

#include <gtest/gtest.h>

using namespace cam::pathfinder;
using namespace cam::math;

// Mock class for testing purposes
class MockPathFinder : public PathFinder {
public:
    bool
    canMove(const Vector2 &pos, const Vector2 &target) const override {
        return PathFinder::canMove(pos, target);
    }

    double
    computeCost(const Node &pos, const Vector2 &target) const override {
        return PathFinder::computeCost(pos, target);
    }

    double
    computeHeuristic(const Vector2 &pos, const Vector2 &target) const override {
        return PathFinder::computeHeuristic(pos, target);
    }

    std::vector<std::vector<Type>>
    parse(const std::vector<std::string> &data) const override {
        return PathFinder::parse(data);
    }
};

TEST(PathFinderTest, ParseMap) {
    MockPathFinder           pathFinder;
    std::vector<std::string> data = {"S.#", "...", "#.E"};

    auto table = pathFinder.parse(data);

    ASSERT_EQ(table.size(), 3);
    ASSERT_EQ(table[0].size(), 3);

    EXPECT_EQ(table[0][0], START);
    EXPECT_EQ(table[0][1], EMPTY);
    EXPECT_EQ(table[0][2], BLOCK);
    EXPECT_EQ(table[2][2], END);
}

TEST(PathFinderTest, SolveSimplePath) {
    MockPathFinder           pathFinder;
    std::vector<std::string> data = {"S...E", "#####", "....."};

    pathFinder.set(data);
    auto solution = pathFinder.solve();

    ASSERT_FALSE(solution.empty());
    EXPECT_EQ(solution.front(), Vector2(0, 0));
    EXPECT_EQ(solution.back(), Vector2(4, 0));
}

TEST(PathFinderTest, SolveWithObstacles) {
    MockPathFinder           pathFinder;
    std::vector<std::string> data = {"S#E", ".#.", "..."};

    pathFinder.set(data);
    auto solution = pathFinder.solve();

    ASSERT_FALSE(solution.empty());
    EXPECT_EQ(solution.front(), Vector2(0, 0));
    EXPECT_EQ(solution.back(), Vector2(2, 0));
    EXPECT_GT(solution.size(), 1);    // Should navigate around obstacles
}

TEST(PathFinderTest, CostCalculation) {
    MockPathFinder           pathFinder;
    std::vector<std::string> data = {"S.#", "...", "#.E"};

    pathFinder.set(data);
    auto   sol  = pathFinder.solve();
    double cost = pathFinder.cost();
    pathFinder.dump();

    EXPECT_GT(cost, 0);    // Ensure cost is calculated
    EXPECT_EQ(pathFinder.computeCost({Vector2(-1, -1), 0, 0, {}}, Vector2(0, 0)), std::numeric_limits<double>::max());
}

TEST(PathFinderTest, HeuristicCalculation) {
    MockPathFinder pathFinder;
    Vector2        start(0, 0);
    Vector2        end(4, 0);

    double heuristic = pathFinder.computeHeuristic(start, end);

    EXPECT_EQ(heuristic, 4.0);    // Manhattan distance in this case
}

TEST(PathFinderTest, CanMove) {
    MockPathFinder           pathFinder;
    std::vector<std::string> data = {"S.#", "...", "#.E"};

    pathFinder.set(data);
    EXPECT_TRUE(pathFinder.canMove(Vector2(0, 0), Vector2(1, 0)));
    EXPECT_FALSE(pathFinder.canMove(Vector2(0, 0), Vector2(0, 2)));
    EXPECT_FALSE(pathFinder.canMove(Vector2(-1, -1), Vector2(-2, -2)));
}
