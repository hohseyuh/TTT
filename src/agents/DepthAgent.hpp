#pragma once
#include "Agent.hpp"

class DepthAgent : public Agent {
public:
    void chooseMove(const Board& board) override;
};
