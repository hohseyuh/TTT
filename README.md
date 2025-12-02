# Tic-Tac-Toe AI Engine

A C++17 implementation of a generalised m×m tic-tac-toe game (also known as m,n,k-game) with multiple AI agents using various search algorithms including Minimax, Alpha-Beta pruning, and depth-limited search with heuristics.

## Features

- **Generalised Board**: Play on any m×m board with k-in-a-row win condition
- **AI Agents**:
  - **Minimax**: Optimal play using exhaustive minimax search
  - **Alpha-Beta**: Optimized minimax with alpha-beta pruning
  - **Depth-Limited**: Scalable heuristic-based search with configurable depth
  - **Random**: Random move selection for testing
- **Performance Statistics**: Real-time AI performance metrics
- **Interactive CLI**: User-friendly command-line interface
- **Benchmarking**: Built-in performance comparison tools

## Project Structure

```
TTT/
├── src/
│   ├── game/           # Core game logic (Board, Rules, KDetector)
│   ├── search/         # Search algorithms (Minimax, AlphaBeta, DepthLimited)
│   ├── agents/         # AI agent implementations
│   ├── ui/cli/         # Command-line interface
│   └── main.cpp        # Application entry point
├── tests/              # Unit tests
├── CMakeLists.txt      # Build configuration
└── README.md           # This file
```

## Building the Project

### Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (MSVC, GCC, or Clang)
- Windows (for ANSI color support in CLI)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Run the executable
./bin/gt_main
```

## How to Use

### Starting the Application

Run the compiled executable to launch the interactive CLI:

```bash
./bin/gt_main
```

### Main Menu Options

1. **Play Game** - Start a new game with current configuration
2. **Configure Game** - Set up board size, win condition, players, and statistics display
3. **Benchmark AI** - Run performance tests on different AI algorithms
4. **Help** - Display information about AI agents
5. **Exit** - Quit the application

### Configuration

Before playing, configure your game settings:

1. Select **Configure Game** from the main menu
2. Enter board size `m` (e.g., 3 for standard tic-tac-toe)
3. Enter win condition `k` (e.g., 3 for 3-in-a-row)
4. Choose Player X agent type
5. Choose Player O agent type
6. Enable/disable AI statistics display

### Playing the Game

- **Human players**: Enter row and column coordinates when prompted (0-indexed)
- **AI players**: Automatically calculate and play their moves
- The board displays after each move
- Game ends when a player wins or the board is full (draw)

### AI Agent Selection

When configuring players, choose from:

1. **Human** - Manual input
2. **Minimax** - Optimal but slow on boards larger than 3×3
3. **Alpha Beta** - More efficient than Minimax, still expensive for large boards
4. **Depth Limited** - Fast and scalable, uses heuristics (requires depth parameter 1-20)
5. **Random** - Random legal moves (for testing)

## Statistics Function

### Overview

The statistics function provides real-time performance metrics for AI agents during gameplay. This feature helps analyze and compare the efficiency of different search algorithms.

### Enabling Statistics

Statistics can be enabled/disabled during game configuration:

1. Go to **Configure Game**
2. When prompted "Show AI statistics? (1 yes, 0 no):", enter `1` to enable or `0` to disable

### Statistics Output

When enabled, after each AI move, the following metrics are displayed:

#### Available Metrics

| Metric | Description | Agents |
|--------|-------------|--------|
| **Nodes** | Total number of game states explored during search | All AI agents |
| **Pruned** | Number of branches pruned (not explored) | Alpha-Beta only |
| **Evaluation** | Minimax value of the chosen move (-1, 0, or 1) | All AI agents |

#### Example Output

```
Player X turn.
Alpha Beta is thinking...
Nodes: 5478
Pruned: 3421
Evaluation: 0
```

### Understanding the Statistics

#### Nodes Explored
- Indicates computational cost of the search
- Higher values = more states examined = slower performance
- Minimax typically explores the most nodes
- Alpha-Beta prunes many nodes, reducing this count
- Depth-Limited explores fewer nodes due to depth cutoff

#### Pruned Branches
- Only applicable to Alpha-Beta algorithm
- Shows how many branches were safely skipped
- Higher pruning = better efficiency
- Pruning effectiveness depends on move ordering

#### Evaluation Value
- **+1**: AI expects to win with optimal play
- **0**: AI expects a draw with optimal play
- **-1**: AI expects to lose with optimal play
- For Depth-Limited, this is a heuristic estimate, not guaranteed

### Accessing Statistics Programmatically

Statistics are stored in the `SearchStats` structure:

```cpp
struct SearchStats {
    int64_t nodesExplored = 0;      // Total nodes visited
    int64_t pruned        = -1;     // Branches pruned (-1 if N/A)
    int     value         = 0;      // Minimax evaluation
    int     maxDepthReached = 0;    // Maximum search depth
    bool    isExact       = true;   // True if exact, false if heuristic
};
```

Access via the `Agent::stats()` method:

```cpp
Agent* agent = /* your agent */;
const SearchStats* stats = agent->stats();
if (stats) {
    std::cout << "Nodes: " << stats->nodesExplored << "\n";
    std::cout << "Value: " << stats->value << "\n";
}
```

### Performance Comparison

Use the **Benchmark** feature to compare AI performance on a standard 3×3 board:

```
Benchmarking on 3x3...
Minimax: 245 ms
Alpha Beta: 87 ms
Depth Limited 6: 12 ms
```

This helps you understand the speed-accuracy tradeoffs between algorithms.

## Technical Details

### Algorithms

- **Minimax**: Complete game tree search with guaranteed optimal play
- **Alpha-Beta Pruning**: Optimized minimax that prunes provably suboptimal branches
- **Depth-Limited Search**: Heuristic evaluation at depth cutoff with move ordering
- **Heuristics**: Evaluates board positions based on potential winning lines

### Performance Considerations

- **3×3 boards**: All algorithms perform well
- **4×4+ boards**: Use Depth-Limited for reasonable performance
- **Minimax/Alpha-Beta**: Exponential time complexity, impractical for large boards
- **Depth-Limited**: Linear in depth, scales to larger boards

### Testing

Run unit tests to verify correctness:

```bash
cd build
ctest
```

Tests cover:
- Game rules and terminal state detection
- K-in-a-row detection
- Minimax correctness
- Alpha-Beta equivalence to Minimax
- Heuristic evaluation
- Deterministic behavior

## Keywords & Concepts

- `static_cast` - Type conversions
- `size_t` - Unsigned integer type for sizes
- `inline` - Function optimization hint
- `optional` - C++17 optional values
- `nullopt` - Empty optional value

## License

This project is for educational purposes.

## Author

Huseyn Movla

<h2 style= "color: #72BF78">Enjoy the game!</h2>