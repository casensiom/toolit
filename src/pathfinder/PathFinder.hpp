#pragma once

#include <math/Vector2.hpp>

#include <string>
#include <vector>

namespace cam::pathfinder {

enum Type {
    EMPTY,
    START,
    END,
    BLOCK
};

struct Cell {
    math::Vector2 pos;
    int32_t type;
};

struct Step {
    int64_t x;
    int64_t y;
    int64_t distance = 0;
    int64_t gcost = -1;
    int64_t hcost = -1;
    int64_t prev = -1;
    bool    found;
};

class PathFinder {
protected:
    virtual std::vector<std::vector<Cell>> parse(const std::vector<std::string> &data) const;
    virtual bool canMove(const std::vector<std::vector<Cell>> &map, const math::Vector2 &from, const math::Vector2 &dir, const math::Vector2 &to) const;
    virtual std::vector<math::Vector2> getValidDirections() const;
    std::vector<math::Vector2> solve_a_star(const std::vector<std::vector<Cell>> &map) const;

    void dump(const std::vector<std::string> &map, const std::vector<math::Vector2> &solution) const;

public:
    PathFinder()  = default;
    ~PathFinder() = default;

    std::vector<math::Vector2> solve(const std::vector<std::string> &data) const;


};

}    // namespace cam::pathfinder