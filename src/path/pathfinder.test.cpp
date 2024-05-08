#include <grid_loader.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <path/pathfinder.hpp>

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

    const Grid grid3 {
            {
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
                0, 0, 0, 0, 0,
            },
            5, 5
        };


    SECTION("A* path found") {
        const auto path = Pathfinder::astar(grid1, {0, 0}, {grid1.rows - 1, grid1.cols - 1});
        REQUIRE(!path.empty());
    }

    SECTION("A* path not found") {
        const auto path = Pathfinder::astar(grid2, {0, 0}, {grid2.rows - 1, grid2.cols - 1});
        REQUIRE(path.empty());
    }

    SECTION("JPS path found") {
        const auto path = Pathfinder::jps(grid1, {0, 0}, {grid1.rows - 1, grid1.cols - 1});
        REQUIRE(!path.empty());
    }

    SECTION("JPS path not found") {
        const auto path = Pathfinder::jps(grid2, {0, 0}, {grid2.rows - 1, grid2.cols - 1});
        REQUIRE(path.empty());
    }

    SECTION("JPS path found in open grid") {
        const auto path = Pathfinder::jps(grid3, {0, 0}, {grid3.rows - 1, grid3.cols - 1});
        REQUIRE(!path.empty());
    }
}

TEST_CASE("JPS large grid", "[Pathfinder]") {
    using namespace path;
    const Grid grid = load_grid("data/maps/map1000_1000_open.txt");
    REQUIRE((grid.rows > 0 && grid.cols > 0));

    const auto path = Pathfinder::jps(grid, {0, 0}, {grid.rows -1, grid.cols-1});
    REQUIRE(!path.empty());
}