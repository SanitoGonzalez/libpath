import sys
sys.path.append("bin/")

from libpath import *
from enum import Enum
from collections import deque


class Agent:
    def __init__(self, position):
        self.position = position
        self.path = None

    def set_path(self, path):
        print("new path:", path)
        self.path = deque(path)

    def update(self):
        if self.path:
            next = self.path.popleft()
            self.position = next


def load_grid(grid_path):
    rows, cols = 0, 0
    data = []

    with open(grid_path, "r") as f:
        lines = list(f)

        rows, cols = map(int, lines[0].split(" "))
        print(f"rows: {rows}, cols: {cols}")
        for line in lines[1:]:
            # print(line)
            data.extend(list(map(int, line.split(" "))))

    return Grid(data, rows, cols)


def run(grid):
    import pygame

    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)
    GRAY = (150, 150, 150)
    RED = (255, 0, 0)
    GREEN = (0, 255, 0)
    BLUE = (0, 0, 255)

    SCREEN_WIDTH, SCREEN_HEIGHT = 1600, 1600
    CELL_SIZE = min(SCREEN_HEIGHT // grid.cols, SCREEN_WIDTH // grid.rows)

    start = Point(0, 0)
    end = Point(grid.rows - 1, grid.cols - 1)

    pygame.init()
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

    agent = Agent(start)
    agent.set_path(Pathfinder.astar(grid, start, end))

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Draw the grid
        screen.fill(WHITE)

        for row in range(grid.rows):
            for col in range(grid.cols):
                color = WHITE
                if grid.at(Point(row, col)) == 1:
                    color = BLACK
                elif Point(row, col) in agent.path:
                    color = BLUE
                # color = WHITE if grid.at(Point(row, col)) == 0 else BLACK
                pygame.draw.rect(screen, color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE))
        pygame.draw.rect(screen, RED, (end.c * CELL_SIZE, end.r * CELL_SIZE, CELL_SIZE, CELL_SIZE))
        pygame.draw.rect(screen, GREEN, (agent.position.c * CELL_SIZE, agent.position.r * CELL_SIZE, CELL_SIZE, CELL_SIZE))

        for row in range(grid.rows + 1):
            pygame.draw.line(screen, GRAY, (0, row * CELL_SIZE), (grid.cols * CELL_SIZE, row * CELL_SIZE))
        for col in range(grid.cols + 1):
            pygame.draw.line(screen, GRAY, (col * CELL_SIZE, 0), (col * CELL_SIZE, grid.rows * CELL_SIZE))



        agent.update()

        pygame.display.flip()
        pygame.time.delay(100)

    pygame.quit()


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("--grid", default="data/maps/map5_5.txt")
    args = parser.parse_args()

    grid = load_grid(args.grid)
    run(grid)
