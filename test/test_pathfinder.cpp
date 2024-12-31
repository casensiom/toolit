#include <pathfinder/PathFinder.hpp>

#include <gtest/gtest.h>

using namespace cam::pathfinder;
using namespace cam::math;

// Mock class for testing purposes
class MockPathFinder : public PathFinder {
public:

    bool canMove(const std::vector<std::vector<Step>> &map, const Vector2 &pos, const Vector2 &target) const override {
        return PathFinder::canMove(map, pos, target);
    }

    double computeCost(const std::vector<std::vector<Step>> &table, const Vector2 &pos, const Vector2 &target) const override {
        return PathFinder::computeCost(table, pos, target);
    }

    double computeHeuristic(const std::vector<std::vector<Step>> &table, const Vector2 &pos, const Vector2 &target) const override {
        return PathFinder::computeHeuristic(table, pos, target);
    }

    std::vector<std::vector<Step>> parse(const std::vector<std::string> &data) const override {
        return PathFinder::parse(data);
    }

    void dump(const std::vector<std::string> &map, const std::vector<Vector2> &solution) const {
        PathFinder::dump(map, solution);
    }
};

TEST(PathFinderTest, ParseMap) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S.#",
        "...",
        "#.E"
    };

    auto table = pathFinder.parse(data);

    ASSERT_EQ(table.size(), 3);
    ASSERT_EQ(table[0].size(), 3);

    EXPECT_EQ(table[0][0].type, START);
    EXPECT_EQ(table[0][1].type, EMPTY);
    EXPECT_EQ(table[0][2].type, BLOCK);
    EXPECT_EQ(table[2][2].type, END);
}

TEST(PathFinderTest, SolveSimplePath) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S...E",
        "#####",
        "....."
    };

    auto solution = pathFinder.solve(data);

    ASSERT_FALSE(solution.empty());
    EXPECT_EQ(solution.front(), Vector2(0, 0));
    EXPECT_EQ(solution.back(), Vector2(4, 0));
}

TEST(PathFinderTest, SolveWithObstacles) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S#E",
        ".#.",
        "..."
    };

    auto solution = pathFinder.solve(data);

    ASSERT_FALSE(solution.empty());
    EXPECT_EQ(solution.front(), Vector2(0, 0));
    EXPECT_EQ(solution.back(), Vector2(2, 0));
    EXPECT_GT(solution.size(), 1); // Should navigate around obstacles
}

TEST(PathFinderTest, CostCalculation) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S.#",
        "...",
        "#.E"
    };

    double cost = pathFinder.cost(data);

    EXPECT_GT(cost, 0); // Ensure cost is calculated
}

TEST(PathFinderTest, HeuristicCalculation) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S...E",
        ".....",
        "....."
    };

    auto table = pathFinder.parse(data);
    Vector2 start(0, 0);
    Vector2 end(4, 0);

    double heuristic = pathFinder.computeHeuristic(table, start, end);

    EXPECT_EQ(heuristic, 4.0); // Manhattan distance in this case
}

TEST(PathFinderTest, CanMove) {
    MockPathFinder pathFinder;
    std::vector<std::string> data = {
        "S.#",
        "...",
        "#.E"
    };

    auto table = pathFinder.parse(data);
    EXPECT_TRUE(pathFinder.canMove(table, Vector2(0, 0), Vector2(1, 0)));
    EXPECT_FALSE(pathFinder.canMove(table, Vector2(0, 0), Vector2(0, 2)));
}
