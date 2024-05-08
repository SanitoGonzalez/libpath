#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <path/pathfinder.hpp>

#include <fstream>
#include <iostream>

path::Grid load_grid(std::string_view grid_path) {
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

TEST_CASE("Pathfinder returns the path", "[Pathfinder]") {
    using namespace path;

    const Grid grid1 {
        {
            0, 0, 0, 0, 0,
            1, 1, 1, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
        },
        5, 5
    };

    const Grid grid2 {
        {
            0, 0, 0, 0, 0,
            1, 1, 1, 1, 1,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
        },
        5, 5
    };


    SECTION("A* search returns the path") {
        SECTION("Path found") {
            const auto path = Pathfinder::astar(grid1, {0, 0}, {grid1.rows - 1, grid1.cols - 1});
            REQUIRE(!path.empty());
        }

        SECTION("Path not found") {
            const auto path = Pathfinder::astar(grid2, {0, 0}, {grid2.rows - 1, grid2.cols - 1});
            REQUIRE(path.empty());
        }
    }

    SECTION("JPS search returns the path") {
        SECTION("Path found") {
            const auto path = Pathfinder::jps(grid1, {0, 0}, {grid1.rows - 1, grid1.cols - 1});
            REQUIRE(!path.empty());
            for (const auto p : path) {
                std::cout << p.to_string() << ", ";
            }
            std::cout << std::endl;
        }

        /*SECTION("Path not found") {
            const auto path = Pathfinder::jps(grid2, {0, 0}, {grid2.rows - 1, grid2.cols - 1});
            REQUIRE(path.empty());
        }*/
    }
}

TEST_CASE("[Pathfinder]") {
    using namespace path;

    SECTION("1000x1000 open") {
        const Grid grid = load_grid("data/maps/map5_5.txt");
        REQUIRE((grid.rows > 0 && grid.cols > 0));

        const Point start {0, 0}, end {grid.rows, grid.cols};

        /*const auto path = Pathfinder::jps(grid, start, end);
        REQUIRE(!path.empty());*/

        /*BENCHMARK("A* - 1000x1000 open") {
            Pathfinder::astar(grid, start, end);
        };

        BENCHMARK("JPS - 1000x1000 open") {
            Pathfinder::jps(grid, start, end);
        };*/
    };
}
