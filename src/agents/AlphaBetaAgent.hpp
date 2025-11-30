#pragma once
#include "Agent.hpp"

class AlphaBetaAgent : public Agent {
public:
    void chooseMove(const Board& board) override;
};
