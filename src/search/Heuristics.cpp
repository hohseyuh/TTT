#include "heuristics.hpp"

namespace search {

    int evaluate(const game::Board &b) {
        // Count X lines − O lines (to be implemented properly)
        int score = 0;
        for (char c : b.grid) {
            if (c == 'X') score += 1;
            if (c == 'O') score -= 1;
        }
        return score;
    }
}
