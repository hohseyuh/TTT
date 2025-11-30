#pragma once
#include "../game/Board.hpp"

using namespace game;

namespace agents {
    class Agent {
    public:
        virtual ~Agent() = default;

        // Returns the chosen move for the current state.
        virtual Move chooseMove(const Board& board) = 0;
    };
}
