# libpath

A*, JPS algorithms library implemented in C++ and bound to Python.

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

### Benchmark
Result from [pathfinder.bench.cpp](src/path/pathfinder.bench.cpp)
```text
# Fully optimized
# CPU = Ryzen 7 6800HS

[Pathfinder]
  1000x1000 open
-------------------------------------------------------------------------------

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
A* - 1000x1000 open                            100             1     9.04856 s 
                                         67.398 ms    66.5044 ms    68.7866 ms 
                                        5.58443 ms     3.9414 ms    7.55746 ms 
                                                                               
JPS - 1000x1000 open                           100             1     7.06599 m 
                                         5.73355 s     5.59556 s     5.84773 s 
                                        640.115 ms    547.335 ms     736.91 ms 
                                                                               

-------------------------------------------------------------------------------
[Pathfinder]
  1000x1000 density 50%
-------------------------------------------------------------------------------

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
A* - 1000x1000 density 50%                     100             1     35.7244 s 
                                        358.383 ms    355.743 ms    361.446 ms 
                                        14.4776 ms    12.4988 ms     17.611 ms 
                                                                               
JPS - 1000x1000 density 50%                    100             1     4.14352 m 
                                         2.40237 s     2.36021 s      2.4287 s 
                                        165.515 ms    107.264 ms    269.261 ms 
                                                                               

-------------------------------------------------------------------------------
[Pathfinder]
  100x100 density 50%
-------------------------------------------------------------------------------

benchmark name                       samples       iterations    est run time
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
A* - 100x100 density 50%                       100             1    174.141 ms 
                                        1.72791 ms     1.7196 ms    1.73636 ms 
                                        42.6544 us    37.5429 us    53.8649 us 
                                                                               
JPS - 100x100 density 50%                      100             1    39.2539 ms 
                                        384.928 us    383.701 us    386.636 us 
                                        7.28925 us     5.6237 us    11.6231 us
```

## Visualizer
```shell
pip install -r requirements.txt
python visualizer.py --grid data/maps/map/map10_10.txt
```