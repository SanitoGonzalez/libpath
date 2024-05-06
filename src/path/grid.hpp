#pragma once

#include <cstdint>
#include <format>
#include <vector>

namespace path {
struct Point {
    size_t r, c;

    struct Hash {
        std::size_t operator()(const Point& p) const {
            return std::hash<size_t> {}(p.r) ^ (std::hash<size_t> {}(p.r) << 1);
        }
    };

    bool operator==(const Point& other) const {
        return r == other.r && c == other.c;
    }

    [[nodiscard]] std::string to_string() const { return std::format("({}, {})", r, c); }
};

struct Grid {
    std::vector<int> data;
    const size_t rows, cols;

    Grid(const std::vector<int>& data, const size_t rows, const size_t cols)
        : data(data), rows(rows), cols(cols) {}

    int& operator()(const Point p) { return data[p.r * cols + p.c]; }
    const int& operator()(const Point p) const { return data[p.r * cols + p.c]; }

    [[nodiscard]] int at(const Point p) const { return data[p.r * cols + p.c]; }

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
    const size_t rows, cols;
};
}
