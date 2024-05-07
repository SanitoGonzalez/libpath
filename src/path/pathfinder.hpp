#pragma once

#include <path/grid.hpp>

#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace path {
class Pathfinder {
public:
    static std::vector<Point> astar(const Grid& grid, Point start, Point end);
    static std::vector<Point> jps(const Grid& grid, Point start, Point end);

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

    const auto probe = [&](Point p, const Point direction, auto&& probe_r)->void {
        const auto [dr, dc] = direction;

        while (grid.is_inside(p)) {
            if (grid.is_blocked(p)) return;
            // if (closed.contains(p)) return;
            // closed.insert(p);

            parents[p] = {p.r - dr, p.c - dc};
            if (p == end) {
                open.push({0, end});
                return;
            }

            // Check forced neighbors
            if (dr * dc > 0) {
                // Diagonal probe
                probe_r(p, {dr, 0}, probe_r);
                probe_r(p, {0, dc}, probe_r);
            } else if (dc > 0) {
                // Horizontal probe
                const Point up {p.r + 1, p.c};
                const Point down {p.r - 1, p.c};

                if (grid.is_inside(up) && grid.is_blocked(up)) {
                    const Point forced_neighbor {up.r, up.c + dc};
                    if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) {
                        open.push({heuristic(p, end), p});
                        return;
                    }
                }
                if (grid.is_inside(down) && grid.is_blocked(down)) {
                    const Point forced_neighbor {down.r, down.c + dc};
                    if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) {
                        open.push({heuristic(p, end), p});
                        return;
                    }
                }
            } else if (dr > 0) {
                // Vertical probe
                const Point right {p.r, p.c + 1};
                const Point left {p.r, p.c - 1};

                if (grid.is_inside(right) && grid.is_blocked(right)) {
                    const Point forced_neighbor {right.r + dr, right.c};
                    if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) {
                        open.push({heuristic(p, end), p});
                        return;
                    }
                }
                if (grid.is_inside(left) && grid.is_blocked(left)) {
                    const Point forced_neighbor {left.r + dr, left.c};
                    if (grid.is_inside(forced_neighbor) && !grid.is_blocked(forced_neighbor)) {
                        open.push({heuristic(p, end), p});
                        return;
                    }
                }
            }

            p.r += dr;
            p.c += dc;
        }
    };

    const auto jump = [&grid, &closed, &probe](const Point p) {
        for (const auto [rt, ct] : grid.get_neighbors(p))
            probe(p, {rt - p.r, ct - p.c}, probe);
        // closed.insert(p);
    };

    open.push({0, start});
    while (!open.empty()) {
        const auto [_f, current] = open.top();
        open.pop();

        if (current == end) return reconstruct_path(parents, end);
        jump(current);
    }

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
