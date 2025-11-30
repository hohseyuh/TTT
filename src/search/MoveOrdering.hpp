#pragma once
#include "../game/Rules.hpp"

namespace search {

    class MoveOrdering {
    public:
        static void orderMoves(const game::Board& board, std::vector<game::Move>& moves);
    };

}