<h3 align="center">TermMaze-Engine</h3>

<p align="center">
A lightweight, console-based maze generator and solver engine written in <b>C++23</b>. It utilizes <b>ANSI</b> escape codes for smooth, flicker-free rendering and classical graph algorithms (<b>DFS</b> and <b>BFS</b>) to generate and solve structures in real time.
</p>

## Key Features

| Feature | Description |
|---|---|
| **Maze Generation (DFS)** | The engine utilizes an optimized Depth-First Search algorithm with a explicit stack (`std::stack`) and a Mersenne Twister generator (`std::mt19937`). |
| **Pathfinding (BFS)** | Implementation of the Breadth-First Search algorithm using a queue (`std::queue`) guarantees finding the mathematically shortest path to the goal. |
| **Smooth Terminal UI** | Grid rendering via direct ANSI cursor positioning (`\033[H`) eliminates screen flickering (no `cls` / `system("cls")`). |
| **Real-Time Animation** | All steps of generation and pathfinding are animated live with precise delay control (`std::this_thread::sleep_for`). |
| **ANSI RGB Styling** | Carefully selected ANSI sequences allow rendering gray walls in RGB space (`\033[48;2;160;160;160m`), a cyan wave for exploration, and a green final route. |


## Workflow

| Stage | Operational Description |
| :---: | :--- |
| **Initialization** | Hiding the terminal cursor (`\033[?25l`) and initializing a full wall grid with dimensions of $25 \times 25$. |
| **Generation** | Dynamic carving of passages starting from point $(1,1)$ with a live animation preview. |
| **Pause** | A 3-second pause upon completing the generation of the full structure. |
| **Solving** | Space exploration via the BFS algorithm, followed by reconstruction and highlighting of the shortest path to destination $(23, 23)$. |
---

## Architecture and Project Logic

This project demonstrates a practical application of graph theory in a console environment without using external graphics libraries.

### Generation Algorithm (Recursive Backtracker / DFS)
Maze generation relies on a randomized depth-first search of a graph using a stack. The use of `std::stack` prevents stack overflow issues inherent to pure recursion:
* **2-Cell Jump:** The generator looks for unvisited neighbors at a distance of $2$ units in up/down/left/right directions ($dx \in \{2, -2, 0, 0\}$, $dy \in \{0, 0, 2, -2\}$).
* **Wall Removal:** After choosing a random direction using `std::uniform_int_distribution`, the engine transforms both the destination cell and the intermediate cell into a path (`PATH`):
  $$\text{point}_{\text{wall}} = \left(x + \frac{dirX}{2}, y + \frac{dirY}{2}\right)$$
* **Backtracking:** When no valid neighbors remain, the engine pops the element from the stack (`s.pop()`) and backtracks to a previous junction.

### Solving Algorithm (Breadth-First Search)
Pathfinding employs breadth-first search, which guarantees path optimality in an unweighted graph:
* **BFS Wave:** A `std::queue<point>` processes upcoming nodes. Each visited cell is temporarily marked with a `.` character (rendered as a cyan ANSI block) and records its predecessor in the `parent[y][x]` array.
* **Path Reconstruction:** Upon reaching the target destination, the engine uses a `while` loop to backtrack from target to start using indices from the `parent` array:
  $$\text{current} = \text{parent}[\text{current}.y][\text{current}.x]$$
  During this process, it updates cells to the `ROUTE` character (`*`), highlighting them in green.
  
### Rendering and ANSI Control Sequences
Using standard terminal control sequences ensures fast and clean rendering:
* **Cursor Positioning:** `\033[H` moves the cursor to the top-left corner instead of clearing the frame buffer, eliminating screen tearing.
* **Background Formatting:** 
  * Wall (`WALL`): `\033[48;2;160;160;160m  \033[0m` (gray color in 24-bit RGB mode).
  * Visited (`.`): `\033[46m  \033[0m` (cyan background).
  * Shortest Route (`ROUTE`): `\033[42m  \033[0m` (green background).
* **Cursor Hiding:** `\033[?25l` disables the blinking cursor during program execution.
---

## Class Structure

* **`Board`**: Represents the 2D grid (`std::vector<std::vector<char>>`). Stores cell state, handles safe access (`isValid`, `getCell`, `setCell`), and manages ANSI cluster rendering.
* **`MazeGenerator`**: Module responsible for building the maze. Operates on a reference to the `Board` object, implementing the random generator and backtracking loop.
* **`MazeSolver`**: Autonomous solver executing the BFS algorithm. Handles exploration wave animation, trace cleanup, and final optimal route reconstruction.
