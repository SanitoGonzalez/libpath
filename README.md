# libpath

A*, JPS and algorithms implemented in C++ and bound to Python.

## Library Usage
### Compile
```shell
mkdir build && cd build
cmake ..
cmake --build . --target path
```
### Import

The compiled shared library can be imported in Python as below.
```python
import sys
sys.path.append("bin/") # path to compiled shared library
from libpath import *
```
`Grid` and `Point` data types can be passed to static methods of `Pathfinder`.
```python
grid = Grid([
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0],
    3, 4)
start = Point(0, 0)
end = Point(2, 3)

print(Pathfinder.astar(grid, start, end))
print(Pathfinder.jps(grid, start, end))
```

Check [visualizer.py](visualizer.py) for further usage.

## Visualizer
```shell
pip install -r requirements.txt
python visualizer.py --grid data/maps/map/map10_10.txt
```