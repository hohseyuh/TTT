#pragma once
#include "heuristics.hpp"
#include "moveOrdering.hpp"
#include "../game/Rules.hpp"

namespace search {

    struct DepthSearchResult {
        int value;
        game::Move move;
    };

    class DepthLimited {
    public:
        static DepthSearchResult run(const game::Board& board, int depth);
    };

}