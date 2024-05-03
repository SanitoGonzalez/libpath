#pragma once

#include <path/Grid.hpp>

#include <unordered_map>

namespace path {
class Navigator {
    static std::vector<Point> navigate_astar(const Grid& grid, Point start, Point end);

    static std::vector<Point> reconstruct_path(const std::unordered_map<Point, Point, Point::Hash>& parents, Point end);
};
}
