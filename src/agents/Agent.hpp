#pragma once
#include "../game/Board.hpp"

class Agent {
public:
    virtual ~Agent() = default;
    virtual void chooseMove(const Board& board) = 0;
};
