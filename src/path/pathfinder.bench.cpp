#include <grid_loader.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <path/pathfinder.hpp>

TEST_CASE("[Pathfinder]") {
    using namespace path;

    SECTION("1000x1000 open") {
        const Grid grid = load_grid("data/maps/map1000_1000_open.txt");
        REQUIRE((grid.rows > 0 && grid.cols > 0));

        const Point start {0, 0}, end {grid.rows - 1, grid.cols - 1};

        BENCHMARK("A* - 1000x1000 open") {
            Pathfinder::astar(grid, start, end);
        };

        BENCHMARK("JPS - 1000x1000 open") {
            Pathfinder::jps(grid, start, end);
        };
    }

    SECTION("1000x1000 density 50%") {
        const Grid grid = load_grid("data/maps/map1000_1000_50.txt");
        REQUIRE((grid.rows > 0 && grid.cols > 0));

        const Point start {0, 0}, end {grid.rows - 1, grid.cols - 1};

        BENCHMARK("A* - 1000x1000 density 50%") {
            Pathfinder::astar(grid, start, end);
        };

        BENCHMARK("JPS - 1000x1000 density 50%") {
            Pathfinder::jps(grid, start, end);
        };
    }

    SECTION("100x100 density 50%") {
        const Grid grid = load_grid("data/maps/map100_100_50.txt");
        REQUIRE((grid.rows > 0 && grid.cols > 0));

        const Point start {0, 0}, end {grid.rows - 1, grid.cols - 1};

        BENCHMARK("A* - 100x100 density 50%") {
            Pathfinder::astar(grid, start, end);
        };

        BENCHMARK("JPS - 100x100 density 50%") {
            Pathfinder::jps(grid, start, end);
        };
    }
}