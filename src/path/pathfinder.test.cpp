#include <catch2/catch_test_macros.hpp>
#include <path/pathfinder.hpp>

TEST_CASE("Pathfinder returns the path", "[Pathfinder]") {
    using namespace path;

    const Grid grid1 {
        {
            0, 0, 0, 0, 0,
            0, 1, 1, 0, 0,
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
        }

        SECTION("Path not found") {
            const auto path = Pathfinder::jps(grid2, {0, 0}, {grid2.rows - 1, grid2.cols - 1});
            REQUIRE(path.empty());
        }
    }
}
