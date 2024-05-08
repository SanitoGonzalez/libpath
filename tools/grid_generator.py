def generate_grid(rows, cols, density):
    import random

    grid = [[0] * cols for i in range(rows)]
    max_length = max(1, int(min(rows, cols) * density))

    def generate_obstacle():
        return random.randint(1, max_length), random.randint(1, max_length)

    max_obstacles = int(rows * cols * density)
    obstacles = 0
    while obstacles < max_obstacles:
        h, w = generate_obstacle()
        r, c = random.randint(0, rows - 1), random.randint(0, cols - 1)

        # Check if new obstacle overrides the start or end
        if r == 0 and c == 0:
            continue
        if r + h >= rows - 1 and c + w >= cols - 1:
            continue

        for i in range(r, r + h):
            if i >= rows:
                break
            for j in range(c, c + w):
                if j >= cols:
                    break
                grid[i][j] = 1
                obstacles += 1

    return grid


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("--rows", required=True, type=int)
    parser.add_argument("--cols", required=True, type=int)
    parser.add_argument("--density", type=float, default=0.3)
    parser.add_argument("--out", type=str, default="map.txt")
    parser.add_argument("--open", type=bool, default=False)
    args = parser.parse_args()

    density_min, density_max = 0.1, 0.7
    if not density_min <= args.density <= density_max:
        raise argparse.ArgumentTypeError(f"density {args.density} is not in range [{density_min}, {density_max}]")

    if args.open:
        grid = [[0] * args.cols for r in range(args.rows)]
    else:
        grid = generate_grid(args.rows, args.cols, args.density)

    with open(args.out, "w") as f:
        f.write(f"{args.rows} {args.cols}\n")
        for row in grid:
            f.write(" ".join(map(str, row)))
            f.write("\n")
