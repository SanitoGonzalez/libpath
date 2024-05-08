#pragma once

#include <path/grid.hpp>

#include <fstream>
#include <iostream>

inline path::Grid load_grid(std::string_view grid_path) {
    std::ifstream file {grid_path.data()};
    if (!file.is_open()) {
        std::cout << "Failed to open grid file" << std::endl;
        return {{}, 0, 0};
    }

    int rows, cols;
    std::vector<int> data {};

    file >> rows >> cols;
    data.resize(rows * cols);

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            file >> data[r * cols + c];

    file.close();

    return {data, rows, cols};
}