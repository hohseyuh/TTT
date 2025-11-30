#pragma once
#include "agent.hpp"
#include "../search/alphaBeta.hpp"

namespace agents {

    class AlphaBetaAgent : public Agent {
    public:
        Move chooseMove(const Board& board) override;
    };

}