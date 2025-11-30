#pragma once
#include "agent.hpp"
#include "../search/minimax.hpp"\

using namespace game;

namespace agents {

    class MinimaxAgent : public Agent {
    public:
        Move chooseMove(const Board& board) override;
    };

}