if __name__ == "__main__":
    rows, cols = 1000, 1000
    grid = [[0] * cols for r in range(rows)]

    for r in range(200, 800):
        for c in range(200, 800):
            grid[r][c] = 1

    with open("data/maps/map1000_1000_square.txt", "w") as f:
        f.write(f"{rows} {cols}\n")
        for row in grid:
            f.write(" ".join(map(str, row)))
            f.write("\n")