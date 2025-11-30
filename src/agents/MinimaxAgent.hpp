#pragma once
#include "Agent.hpp"

class MinimaxAgent : public Agent {
public:
    void chooseMove(const Board& board) override;
};
