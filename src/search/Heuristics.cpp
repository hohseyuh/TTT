#include "heuristics.hpp"
using namespace std;
using namespace game;

namespace search {

// Simple placeholder; we will refine later.
int Heuristics::evaluate(const Board& board) {
    // Count X lines − O lines (to be implemented properly)
    int score = 0;
    for (char c : board.grid) {
        if (c == 'X') score += 1;
        if (c == 'O') score -= 1;
    }
    return score;
}

} // namespace search
