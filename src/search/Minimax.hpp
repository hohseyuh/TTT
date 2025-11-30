#pragma once
#include "../game/Rules.hpp"
#include <bits/stdc++.h>

using namespace game;

namespace search {

    struct MinimaxResult {
        int value; // utility value
        Move move; // chosen move
    };

    class Minimax {
    public:
        // Computes the best move for the current player using plain Minimax.
        static MinimaxResult run(const Board& board);
    };

}
