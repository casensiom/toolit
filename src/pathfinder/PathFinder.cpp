#include "PathFinder.hpp"

#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace cam::math;

namespace cam::pathfinder {

std::vector<std::vector<Type>>
PathFinder::parse(const std::vector<std::string> &data) const {
    const size_t                   HEIGHT = data.size();
    const size_t                   WIDTH  = data[0].size();
    std::vector<std::vector<Type>> ret(HEIGHT, std::vector<Type>(WIDTH, EMPTY));
    for(size_t y = 0; y < HEIGHT; y++) {
        for(size_t x = 0; x < WIDTH; x++) {
            if(data[y][x] == '.') {
                ret[y][x] = EMPTY;
            } else if(data[y][x] == 'S') {
                ret[y][x] = START;
            } else if(data[y][x] == 'E') {
                ret[y][x] = END;
            } else if(data[y][x] == '#') {
                ret[y][x] = BLOCK;
            }
        }
    }

    return ret;
}

bool
PathFinder::inside(const Vector2 &pos) const {
    return (pos.getY() >= 0 && pos.getX() >= 0 && pos.getY() < map.size() && pos.getX() < map[pos.getY()].size());
}

bool
PathFinder::canMove(const Vector2 &pos, const Vector2 &target) const {
    if(inside(target)) {
        return (map[target.getY()][target.getX()] != BLOCK);
    }
    return false;
}

std::vector<Vector2>
PathFinder::getValidDirections() const {
    return {
        { 0, -1},
        { 1,  0},
        { 0,  1},
        {-1,  0}
    };
}

double
PathFinder::computeHeuristic(const Vector2 &pos, const Vector2 &target) const {
    return pos.distance(target, MANHATTAN);
}

/// @brief This methods returns the first node status. The node is composed by the cell position, the score at this position, the direction
/// index inside the valid direction array and the path to the current cell position (this last one included).
/// @param start This param indicates the position of the start cell.
/// @return A node object representing the initial search status.
Node
PathFinder::onStart(const Vector2 &start) const {
    return {start, 0, 0, {start}};
}

struct Position {
    int x;
    int y;
    int dir;

    // Operador de comparación estricta
    bool
    operator<(const Position &other) const {
        if(x != other.x) {
            return x < other.x;
        }
        if(y != other.y) {
            return y < other.y;
        }
        return dir < other.dir;
    }
};

std::vector<math::Vector2>
PathFinder::solve_a_star() {
    math::Vector2 start, end;

    for(size_t y = 0; y < map.size(); ++y) {
        for(size_t x = 0; x < map[y].size(); ++x) {
            if(map[y][x] == START) {
                start.set(x, y);
            } else if(map[y][x] == END) {
                end.set(x, y);
            }
        }
    }

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::map<Position, int>                                          visited;

    auto dirs = getValidDirections();
    minCost   = std::numeric_limits<double>::max();
    openSet.push(onStart(start));
    while(!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if(current.g > minCost) {
            continue;
        }

        if(current.pos == end) {
            if(current.g < minCost) {
                minCost = current.g;
                equivalentPaths.clear();
            }

            if(current.g == minCost) {
                equivalentPaths.push_back(current.path);
            }
            continue;
        }

        for(size_t idx = 0; idx < dirs.size(); idx++) {
            const auto &dir = dirs[idx];

            math::Vector2 neighbor = current.pos + dir;

            if(!canMove(current.pos, neighbor)) {
                continue;
            }
            if(std::find(current.path.begin(), current.path.end(), neighbor) != current.path.end()) {
                continue;
            }

            double tentativeG = computeCost(current, neighbor);
            if(tentativeG > minCost) {
                continue;
            }

            auto it = visited.find({(int)neighbor.getX(), (int)neighbor.getY(), (int)idx});
            if(it != visited.end()) {
                if(it->second < tentativeG) {
                    continue;
                }
            }
            visited[{(int)neighbor.getX(), (int)neighbor.getY(), (int)idx}] = tentativeG;

            auto copy = current.path;
            copy.push_back(neighbor);
            openSet.push({neighbor, tentativeG, (int)idx, copy});
        }
    }

    return !equivalentPaths.empty() ? equivalentPaths.front() : std::vector<math::Vector2>();
}

void
PathFinder::dump() const {
    const size_t HEIGHT = map.size();
    const size_t WIDTH  = map[0].size();

    std::stringstream ss;
    ss << std::endl;
    for(size_t y = 0; y < HEIGHT; y++) {
        for(size_t x = 0; x < WIDTH; x++) {
            if(map[y][x] == BLOCK) {
                ss << "#";
            } else if(std::find(solution.begin(), solution.end(), Vector2(x, y)) != solution.end()) {
                ss << "+";
            } else {
                bool found = false;
                for(const auto &l : equivalentPaths) {
                    if(std::find(l.begin(), l.end(), Vector2(x, y)) != l.end()) {
                        found = true;
                        break;
                    }
                }
                ss << (found ? "x" : " ");
            }
        }
        ss << std::endl;
    }

    std::cout << ss.str();
}

void
PathFinder::set(const std::vector<std::string> &data) {
    map = parse(data);
}

std::vector<math::Vector2>
PathFinder::solve() {
    solution = solve_a_star();
    return solution;
}

std::vector<std::vector<math::Vector2>>
PathFinder::alternatives() const {
    return equivalentPaths;
}
double
PathFinder::cost() const {
    return minCost;
}

double
PathFinder::computeCost(const Node &current, const Vector2 &target) const {
    if(inside(current.pos) && inside(target)) {
        return current.g + computeHeuristic(current.pos, target);
    }
    return std::numeric_limits<double>::max();
}

}    // namespace cam::pathfinder