#pragma once
#include "../game/Board.hpp"

namespace search {
    class Heuristics {
    public:
        // Evaluates non-terminal board states for larger m,k.
        // Positive favors X, negative O.
        static int evaluate(const game::Board& board);
    };
}
