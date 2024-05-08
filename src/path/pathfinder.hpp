#pragma once

#include <path/grid.hpp>

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace path {
class Pathfinder {
public:
    static std::vector<Point> astar(const Grid& grid, Point start, Point end);
    static std::vector<Point> jps(const Grid& grid, Point start, Point end);
    static std::vector<Point> jps_b(const BitGrid& grid, Point start, Point end);

private:
    static std::vector<Point> reconstruct_path(const std::unordered_map<Point, Point, Point::Hash>& parents, Point end);
};

inline std::vector<Point> Pathfinder::astar(const Grid& grid, const Point start, const Point end) {
    struct Node {
        int f;
        Point p;
    };
    const auto node_cmp = [](const Node& n1, const Node& n2) { return n1.f > n2.f; };
    const auto heuristic = [](const Point p1, const Point p2) { return Point::manhattan_distance(p1, p2); };

    std::priority_queue<Node, std::vector<Node>, decltype(node_cmp)> open {node_cmp};
    std::unordered_set<Point, Point::Hash> closed {};
    std::unordered_map<Point, Point, Point::Hash> parents {};
    std::unordered_map<Point, int, Point::Hash> g {{start, 0}};

    open.push({0, start});
    while (!open.empty()) {
        const auto [_f, current] = open.top();
        open.pop();
        closed.insert(current);

        if (current == end) return reconstruct_path(parents, end);

        for (const auto next : grid.get_neighbors(current)) {
            if (closed.contains(next)) continue;
            if (grid.is_blocked(next)) continue;

            const auto g_next = g[current] + heuristic(current, next);
            if (g.contains(next) && g_next >= g[next]) continue;

            parents[next] = current;

            g[next] = g_next;
            const auto f = g_next + heuristic(next, end);
            open.push({f, next});
        }
    }

    return {};
}

inline std::vector<Point> Pathfinder::jps(const Grid& grid, const Point start, const Point end) {
    struct Node {
        int f;
        Point p;
    };
    const auto node_cmp = [](const Node& n1, const Node& n2) { return n1.f > n2.f; };
    const auto heuristic = [](const Point p1, const Point p2) { return Point::manhattan_distance(p1, p2); };

    std::priority_queue<Node, std::vector<Node>, decltype(node_cmp)> open {node_cmp};
    std::unordered_set<Point, Point::Hash> closed {};
    std::unordered_map<Point, Point, Point::Hash> parents {};

    const auto has_forced_neighbor = [&](const Point p, const Point direction)->bool {
        if (!grid.is_inside(p) || !grid.is_blocked(p)) return false;

        const auto [dr, dc] = direction;
        if (dc * dc > 0) {
            // Horizontal
            const Point forced_neighbor {p.r, p.c + dc};
            if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) return true;
        } else if (dr * dr > 0) {
            // Vertical
            const Point forced_neighbor {p.r + dr, p.c};
            if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) return true;
        }
        return false;
    };

    const auto probe = [&](Point p, const Point direction, auto&& probe_r)->bool {
        const auto [dr, dc] = direction;

        while (grid.is_inside(p)) {
            if (grid.is_blocked(p)) return false;

            // std::cout << std::format("{}, {}", p.to_string(), direction.to_string()) << std::endl;

            parents[p] = {p.r - dr, p.c - dc};
            if (p == end) {
                // open.push({0, end});
                return true;
            }

            if (dr * dc != 0) {
                // Diagonal probe
                const Point front {p.r - dr, p.c};
                const Point back {p.r, p.c - dc};

                if (has_forced_neighbor(front, {dr, 0}) || has_forced_neighbor(back, {0, dc})) {
                    open.push({heuristic(p, end), p});
                    return true;
                }

                bool found_forced_neighbor = false;
                found_forced_neighbor |= probe_r({p.r + dr, p.c}, {dr, 0}, probe_r);
                found_forced_neighbor |= probe_r({p.r, p.c + dc}, {0, dc}, probe_r);

                if (found_forced_neighbor) {
                    open.push({heuristic(p, end), p});
                    return true;
                }
            }
            else if (dc * dc > 0) {
                // Horizontal probe
                const Point up {p.r + 1, p.c};
                const Point down {p.r - 1, p.c};

                if (has_forced_neighbor(up, direction) || has_forced_neighbor(down, direction)) {
                    open.push({heuristic(p, end), p});
                    return true;
                }
            } else if (dr * dr > 0) {
                // Vertical probe
                const Point right {p.r, p.c + 1};
                const Point left {p.r, p.c - 1};

                if (has_forced_neighbor(right, direction) || has_forced_neighbor(left, direction)) {
                    open.push({heuristic(p, end), p});
                    return true;
                }
            }

            closed.insert(p);
            p.r += dr;
            p.c += dc;
        }
        return false;
    };

    const auto jump = [&grid, &closed, &probe](const Point p) {
        closed.insert(p);
        for (const auto neighbor : grid.get_neighbors(p)) {
            if (closed.contains(neighbor) || grid.is_blocked(neighbor)) continue;
            /*std::cout << std::format(
                "{} -> {}, {}", p.to_string(), neighbor.to_string(),
                Point(neighbor.r - p.r, neighbor.c - p.c).to_string()) << std::endl;*/
            probe(neighbor, {neighbor.r - p.r, neighbor.c - p.c}, probe);
        }
    };

    open.push({0, start});
    while (!open.empty()) {
        const auto [_f, current] = open.top();
        open.pop();
        jump(current);

        if (parents.contains(end)) return reconstruct_path(parents, end);
    }

    return {};
}

inline std::vector<Point> Pathfinder::jps_b(const BitGrid& grid, Point start, Point end) {
    return {};
}

inline std::vector<Point> Pathfinder::reconstruct_path(
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
