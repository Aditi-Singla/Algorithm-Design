## Assignment 5 - Network Flow

**The Tiling problem:** There is an n × n grid (1 ≤ n ≤ 500) in which some cells are empty and some are filled. The empty/filled cells are given by an n × n matrix F . Cell (i, j) is empty iff F [i, j] = 1. You have unbounded supply of 2 × 1 tiles (called dominoes). Each domino could be placed on the empty cells of the grid in horizontal and vertical manner (note that you need two consecutive empty cells on the grid for doing this). The problem is to determine if placing these 2 × 1 dominos such that each empty cell is covered by exactly one domino can cover the grid. If such a tiling is possible, then you should also give a tiling.

#### Running the code (in [./src](./src) folder)

1. To compile -

    ```bash
    ./compile.sh
    ```

2. To run - 

    ```bash
    ./run.sh <input> <output>
    ```