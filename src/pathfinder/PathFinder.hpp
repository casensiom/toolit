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

struct Step {
    int32_t type;
    double  distance = 0;
    double  gcost = 0;
    double  hcost = 0;
    bool    found = false;
    math::Vector2 prev;
};

class PathFinder {
protected:
    virtual void foundStart(std::vector<std::vector<Step>> &table, const math::Vector2 &pos) const;
    virtual void foundEnd(std::vector<std::vector<Step>> &table, const math::Vector2 &pos) const;
    virtual bool canMove(const std::vector<std::vector<Step>> &map, const math::Vector2 &pos, const math::Vector2 &target) const;
    
    virtual std::vector<math::Vector2> getValidDirections() const;
    virtual double computeCost(const std::vector<std::vector<Step>> &table, const math::Vector2 &pos, const math::Vector2 &target) const;
    virtual double computeHeuristic(const std::vector<std::vector<Step>> &table, const math::Vector2 &pos, const math::Vector2 &target) const;

    virtual std::vector<std::vector<Step>> parse(const std::vector<std::string> &data) const;
    
    std::vector<math::Vector2> solve_a_star(std::vector<std::vector<Step>> &map) const;

    void dump(const std::vector<std::string> &map, const std::vector<math::Vector2> &solution) const;

public:
    PathFinder()  = default;
    ~PathFinder() = default;

    std::vector<math::Vector2> solve(const std::vector<std::string> &data) const;
    double cost(const std::vector<std::string> &data) const;
};

}    // namespace cam::pathfinder