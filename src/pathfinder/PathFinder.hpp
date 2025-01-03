#pragma once

#include <math/Vector2.hpp>

#include <string>
#include <vector>

namespace cam::pathfinder {

enum Type { EMPTY, START, END, BLOCK };

struct Node {
    math::Vector2              pos;
    double                     g;
    int                        dir;
    std::vector<math::Vector2> path;

    bool
    operator>(const Node &other) const {
        return g > other.g;
    }
};

class PathFinder {
protected:
    std::vector<std::vector<Type>>          map;
    std::vector<math::Vector2>              solution;
    std::vector<std::vector<math::Vector2>> equivalentPaths;
    double                                  minCost;

protected:
    virtual Node                           onStart(const math::Vector2 &pos) const;
    virtual bool                           inside(const math::Vector2 &pos) const;
    virtual bool                           canMove(const math::Vector2 &pos, const math::Vector2 &target) const;
    virtual std::vector<math::Vector2>     getValidDirections() const;
    virtual double                         computeCost(const Node &current, const math::Vector2 &target) const;
    virtual double                         computeHeuristic(const math::Vector2 &pos, const math::Vector2 &target) const;
    virtual std::vector<std::vector<Type>> parse(const std::vector<std::string> &data) const;
    std::vector<math::Vector2>             solve_a_star();

public:
    PathFinder()  = default;
    ~PathFinder() = default;

    void                                    set(const std::vector<std::string> &data);
    std::vector<math::Vector2>              solve();
    std::vector<std::vector<math::Vector2>> alternatives() const;
    double                                  cost() const;
    void                                    dump() const;
};

}    // namespace cam::pathfinder