#pragma once
#include "../game/Rules.hpp"
#include <bits/stdc++.h>

namespace search {

    struct AlphaBetaResult {
        int value;
        game::Move move;
    };

    class AlphaBeta {
    public:
        static AlphaBetaResult run(const game::Board& board);
    };

}