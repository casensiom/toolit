#include "PathFinder.hpp"

#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <iostream>

using namespace cam::math;

namespace cam::pathfinder {


void
PathFinder::foundStart(std::vector<std::vector<Step>> &table, const math::Vector2 &pos) const {
    // do nothing
}

void
PathFinder::foundEnd(std::vector<std::vector<Step>> &table, const math::Vector2 &pos) const {
    // do nothing
}

std::vector<std::vector<Step>> 
PathFinder::parse(const std::vector<std::string> &data) const {
    const size_t HEIGHT = data.size();
    const size_t WIDTH  = data[0].size();
    std::vector<std::vector<Step>> ret(HEIGHT, std::vector<Step>(WIDTH, Step()));
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            if(data[y][x] == '.') {
                ret[y][x].type = EMPTY;
            } else if(data[y][x] == 'S') {
                ret[y][x].type = START;
            } else if(data[y][x] == 'E') {
                ret[y][x].type = END;
            } else if(data[y][x] == '#') {
                ret[y][x].type = BLOCK;
            }
        }
    }
    
    return ret;
}

bool
PathFinder::canMove(const std::vector<std::vector<Step>> &map, const Vector2 &pos, const Vector2 &target) const {
    return (map[target.getY()][target.getX()].type != BLOCK);
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
PathFinder::computeCost(const std::vector<std::vector<Step>> &table, const Vector2 &pos, const Vector2 &target) const {
    return table[pos.getY()][pos.getX()].gcost + computeHeuristic(table, pos, target);
}

double
PathFinder::computeHeuristic(const std::vector<std::vector<Step>> &table, const Vector2 &pos, const Vector2 &target) const {
    return pos.distance(target, MANHATTAN);
}

std::vector<Vector2>
PathFinder::solve_a_star(std::vector<std::vector<Step>> &table) const {
    const size_t HEIGHT = table.size();
    const size_t WIDTH  = table[0].size();
    std::queue<Vector2> q;
    Vector2 start;
    Vector2 end;

    //Create a map
    for (int64_t y = 0; y < HEIGHT; ++y) {
        for (int64_t x = 0; x < WIDTH; ++x) {
            if(table[y][x].type == START) {
                start.set(x, y);
                foundStart(table, start);
            } else if(table[y][x].type == END) {
                end.set(x, y);
                foundEnd(table, end);
            }
        }
    }
    
    auto dirs = getValidDirections();

    q.push(start);
    while(!q.empty()) {
        Vector2 current = q.front();
        q.pop();

        if (current == end) {
            continue;
        }
        table[current.getY()][current.getX()].found = true;

        for(const auto &direction : dirs) {

            Vector2 nextPos = current + direction;
            int64_t x = nextPos.getX();
            int64_t y = nextPos.getY();

            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                continue;
            }

            Step &next = table[y][x];
            if(!canMove(table, current, nextPos)) {
                continue;
            }
            if (next.found) {
                continue;
            }

            double gcost = computeCost(table, current, nextPos);
            if (next.distance == 0 || next.gcost > gcost) {
                next.gcost = gcost;
                next.hcost = computeHeuristic(table, nextPos, end);
                next.distance = next.gcost + next.hcost;
                next.prev = current;
                q.push(nextPos);
            }
            
        }
    }



    Vector2 current = end;
    std::vector<Vector2> solution;
    while (current == end || (current != start && table[current.getY()][current.getX()].found)) {
        solution.push_back(current);
        current = table[current.getY()][current.getX()].prev;
    }
    if(!solution.empty()) {
        solution.push_back(start);
    }
    std::reverse(solution.begin(), solution.end());
    return solution;
}



void
PathFinder::dump(const std::vector<std::string> &map, const std::vector<Vector2> &solution) const {

    const size_t HEIGHT = map.size();
    const size_t WIDTH  = map[0].size();
    std::vector<std::string> copy = map;

    for(const auto &p : solution) {
        copy[p.getY()][p.getX()] = '+';
    }

    for(const auto &l : copy) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl;
}

std::vector<math::Vector2>
PathFinder::solve(const std::vector<std::string> &data) const {
    auto map = parse(data);
    auto ret = solve_a_star(map);
    dump(data, ret);
    return ret;
}

double
PathFinder::cost(const std::vector<std::string> &data) const {
    auto map = parse(data);
    auto sol = solve_a_star(map);
    return map[sol.back().getY()][sol.back().getX()].gcost;
}


}