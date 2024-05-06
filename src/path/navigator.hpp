#pragma once

#include <path/grid.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <queue>
#include <unordered_map>

namespace path {
class Navigator {
public:
    static std::vector<Point> navigate_astar(const Grid& grid, Point start, Point end);
    static std::vector<Point> reconstruct_path(const std::unordered_map<Point, Point, Point::Hash>& parents, Point end);
};

inline std::vector<Point> Navigator::navigate_astar(const Grid& grid, const Point start, const Point end) {
    struct Node {
        int f;
        int g;
        Point p;
    };
    const auto node_cmp = [](const Node& n1, const Node& n2) {
        return n1.f > n2.f;
    };

    const auto heuristic = [end](const Point p) {
        // Octile distance; Cost of cardinal move = 1, Cost of diagonal move = 1
        return std::abs(static_cast<int>(p.c - end.c)) + std::abs(static_cast<int>(p.r - end.r));
    };

    std::priority_queue<Node, std::vector<Node>, decltype(node_cmp)> open {node_cmp};
    std::unordered_map<Point, bool, Point::Hash> closed {};
    std::unordered_map<Point, Point, Point::Hash> parents {};
    std::unordered_map<Point, int, Point::Hash> g {{start, 0}};

    open.push({0, 0, start});
    while (!open.empty()) {
        const auto [_, g_temp, current] = open.top();
        open.pop();
        closed[current] = true;
        if (g_temp < g[current]) continue;

        for (const auto next : grid.get_neighbors(current)) {
            if (closed.contains(next)) continue;
            if (grid(next)) continue;

            const auto g_next = g[current] + 1;
            if (g.contains(next) && g_next >= g[next]) continue;

            parents[next] = current;
            if (next == end) return reconstruct_path(parents, next);

            g[next] = g_next;
            const auto f = g_next + heuristic(next);
            open.push({f, g_next, next});
        }
    }

    return {};
}

inline std::vector<Point> Navigator::reconstruct_path(
    const std::unordered_map<Point, Point, Point::Hash>& parents, Point end) {
    std::vector<Point> path {end};
    auto current = end;
    while (parents.contains(current)) {
        current = parents.at(current);
        path.push_back(current);
    }
    std::reverse(std::begin(path), std::end(path));
    return path;
}
}
