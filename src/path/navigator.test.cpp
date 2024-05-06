#include <catch2/catch_test_macros.hpp>
#include <path/navigator.hpp>

TEST_CASE("Navigator returns the path", "[Navigator]") {
    using namespace path;

    constexpr size_t ROWS {6}, COLS {6};
    constexpr Point start {0, 0}, end {ROWS - 1, COLS - 1};
    const Grid grid1 {
        {
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 1, 1, 1, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
        },
        ROWS, COLS
    };
    const Grid grid2 {
        {
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
        },
        ROWS, COLS
    };


    SECTION("A* search returns the path") {
        SECTION("Path found") {
            const auto path = Navigator::navigate_astar(grid1, start, end);
            REQUIRE(!path.empty());
        }

        SECTION("Path not found") {
            const auto path = Navigator::navigate_astar(grid2, start, end);
            REQUIRE(path.empty());
        }
    }
}
