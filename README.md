# Eight Puzzle Solver

- Implemented an Eight Puzzle Solver by creating a non-redundant tree of the 3 by 3 puzzle grid
- Implemented Depth-First search, Iterative Deepening Search, A* search using Manhattan and Misplaced Tiles heuristics to search through the tree
- Of the two heuristics used for A*, the Manhattan heuristic calculates the displacement of each tile from its goal position while the Misplaced Tiles heuristic just calculates the number of tiles misplaced from the goal position, comparatively the Misplaced tiles heuristic should be a faster as the reduced number of misplaced tiles while travelling from node to node should get you to the goal state faster.

# Build

- Linux
  - Clone the repository and run the specific algorithm by using the make "algorithm_name" to view the results in the terminal

- Windows
  - Using g++, run the following commands in the windows terminal to view the results of the algorithm in the windows terminal

    g++ main.cc -o "executable_name"; { executable_name: anything }
    
    ./"executable_name" "algorithm_name" input.txt { algorithm_name: dfs, ids, astar1, astar2 }
