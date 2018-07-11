## Assignment 4 - Dynamic Programming

**The egg drop problem:** There is a building with n floors. You have identical eggs with the property that any egg will break iff thrown from floor B and above. If an egg breaks, you cannot fix and reuse it. You want to determine the value of B. Consider the case where you only have one egg. In this case, the worst-case number of trials needed is n − 1 since the value of B may be equal to n and the only strategy is to start dropping the egg from floor 1, 2, 3, ..., n − 1. Now, suppose you have two eggs. Consider the strategy that minimizes the number of trials in the worst-case. Let this worst-case number of trials be denoted by T (n, 2). Similarly, we can define T (n, 3), T (n, 4), ... (for 3 eggs, 4 eggs etc.). Design an algorithm to compute the value of T (n, k) for any given k(1 ≤ k ≤ 100) and n(1 ≤ n ≤ 10000). You may assume that 1 ≤ B ≤ n.

#### Running the code (in [./src](./src) folder)

1. To compile -

    ```bash
    ./compile.sh
    ```

2. To run - 

    ```bash
    ./run.sh <input> <output>
    ```