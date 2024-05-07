#pragma once

#include <cmath>
#include <cstdint>
#include <format>
#include <vector>

namespace path {
struct Point {
    int r, c;

    struct Hash {
        int operator()(const Point& p) const {
            return std::hash<int> {}(p.r) ^ (std::hash<int> {}(p.r) << 1);
        }
    };

    [[nodiscard]] std::string to_string() const { return std::format("({}, {})", r, c); }

    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }

    static int manhattan_distance(const Point p1, const Point p2) {
        return std::abs(p1.c - p2.c) + std::abs(p1.r - p2.r);
    }

    static float euclidean_distance(const Point p1, const Point p2) {
        return std::sqrtf(static_cast<float>((p1.c - p2.c) * (p1.c - p2.c)) + static_cast<float>((p1.r - p2.r) * (p1.r - p2.r)));
    }
};

struct Grid {
    std::vector<int> data;
    const int rows, cols;

    Grid(const std::vector<int>& data, const int rows, const int cols)
        : data(data), rows(rows), cols(cols) {}

    [[nodiscard]] int at(const Point p) const { return data[p.r * cols + p.c]; }
    [[nodiscard]] bool is_blocked(const Point p) const { return at(p) == 1; }
    [[nodiscard]] bool is_inside(const Point p) const { return 0 <= p.r && p.r < rows && 0 <= p.c && p.c < cols; }

    [[nodiscard]] std::vector<Point> get_neighbors(const Point p) const {
        std::vector<Point> neighbors {};
        if (p.c < cols - 1) neighbors.push_back({.r = p.r, .c = p.c + 1});
        if (p.c >= 1) neighbors.push_back({.r = p.r, .c = p.c - 1});
        if (p.r < rows - 1) neighbors.push_back({.r = p.r + 1, .c = p.c});
        if (p.r >= 1) neighbors.push_back({.r = p.r - 1, .c = p.c});
        if (p.c < cols - 1 && p.r < rows - 1) neighbors.push_back({.r = p.r + 1, .c = p.c + 1});
        if (p.c < cols - 1 && p.r >= 1) neighbors.push_back({.r = p.r - 1, .c = p.c + 1});
        if (p.c >= 1 && p.r < rows - 1) neighbors.push_back({.r = p.r + 1, .c = p.c - 1});
        if (p.c >= 1 && p.r >= 1) neighbors.push_back({.r = p.r - 1, .c = p.c - 1});
        return neighbors;
    }
};

struct BitGrid {
    std::vector<uint64_t> data;
    const int rows, cols;
};
}
