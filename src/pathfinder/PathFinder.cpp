#include "PathFinder.hpp"

#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <iostream>

using namespace cam::math;

namespace cam::pathfinder {


std::vector<std::vector<Cell>> 
PathFinder::parse(const std::vector<std::string> &data) const {

    const size_t HEIGHT = data.size();
    const size_t WIDTH  = data[0].size();
    std::vector<std::vector<Cell>> ret(HEIGHT, std::vector<Cell>(WIDTH, Cell()));
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
PathFinder::canMove(const std::vector<std::vector<Cell>> &map, const Vector2 &from, const Vector2 &dir, const Vector2 &to) const {
    return (map[to.getY()][to.getX()].type != BLOCK);
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

std::vector<Vector2>
PathFinder::solve_a_star(const std::vector<std::vector<Cell>> &map) const {
    const size_t HEIGHT = map.size();
    const size_t WIDTH  = map[0].size();
    std::vector<Step> table(HEIGHT * WIDTH, Step());
    std::queue<size_t> q;
    Vector2 start;
    Vector2 end;

    //Create a map
    for (int64_t y = 0; y < HEIGHT; ++y) {
        for (int64_t x = 0; x < WIDTH; ++x) {
            table[y * WIDTH + x] = { x, y, 0, -1, -1, -1, false }; // cell
            if(map[y][x].type == START) {
                start.set(x, y);
            } else if(map[y][x].type == END) {
                end.set(x, y);
            }
        }
    }

    q.push(start.getY() * WIDTH + start.getX());

    while(!q.empty()) {
        size_t idx = q.front();
        q.pop();

        table[idx].found = true;
        if (end.getY() == table[idx].y && end.getX() == table[idx].x) {
            break;
        }
        
        auto dirs = getValidDirections();

        for(const auto &direction : dirs) {

            int64_t x = table[idx].x + direction.getX();
            int64_t y = table[idx].y + direction.getY();

            if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
                continue;
            }

            size_t offset = y * WIDTH + x;
            if (table[offset].x != x || table[offset].y != y) {
                continue;
            }
            if(!canMove(map, Vector2(table[idx].x, table[idx].y), direction, Vector2(x, y))) {
                continue;
            }
            if (table[offset].found) {
                continue;
            }

            int64_t gcost = table[idx].gcost + std::hypot(y - table[idx].y, x - table[idx].x);
            if (table[offset].distance == 0 || table[offset].gcost > gcost) {
                table[offset].gcost = gcost;
                table[offset].hcost = std::hypot(y - end.getY(), x - end.getX());
                table[offset].distance = table[offset].gcost + table[offset].hcost;
                table[offset].prev = idx;
                q.push(offset);
            }
            
        }
    }


    size_t current = end.getY() * WIDTH + end.getX();
    std::vector<Vector2> solution;
    while (table[current].prev != -1) {
        solution.emplace_back(table[current].x, table[current].y);
        current = table[current].prev;
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

}