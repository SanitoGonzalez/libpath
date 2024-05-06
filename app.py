import sys
sys.path.append("bin/")
from libpath import *
from enum import Enum

class Agent:
    class State(Enum):
        IDLE = 1

    def __init__(self):
        self.state = Agent.State.IDLE

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
    RED = (255, 0, 0)
    GREEN = (0, 255, 0)
    BLUE = (0, 0, 255)
    # CELL_SIZE =

    start = Point(0, 0)
    end = Point(grid.rows - 1, grid.cols - 1)

    pygame.init()
    screen = pygame.display.set_mode((800, 600))

    agent = Agent()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Draw the grid
        screen.fill(WHITE)
        for row in range(grid.rows):
            for col in range(grid.cols):
                color = WHITE if grid.at(Point(row, col)) == 0 else BLACK
                pygame.draw.rect(screen, color, (col * 40, row * 40, 40, 40))

        pygame.draw.rect(screen, GREEN, (start.c * 40, start.r * 40, 40, 40))
        pygame.draw.rect(screen, RED, (end.c * 40, end.r * 40, 40, 40))

        # Update the agent

        pygame.display.flip()
        pygame.time.delay(100)


    pygame.quit()

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("--grid", default="data/maps/map10_10.txt")
    args = parser.parse_args()

    grid = load_grid(args.grid)
    run(grid)
