def read_grid(grid_path):
    rows, cols = 0, 0
    grid = []

    with open(grid_path, "r") as f:
        lines = list(f)

        rows, cols = map(int, lines[0].split(" "))
        for line in lines:
            grid.append(list(map(int, line.split(" "))))

    return grid


if __name__ == "__main__":
    import sys
    import argparse

    # Add libpath.so
    sys.path.append("bin/")

    from libpath import Point

