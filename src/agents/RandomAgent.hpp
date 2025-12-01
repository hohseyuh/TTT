#pragma once
#include "Agent.hpp"

using namespace game;

class RandomAgent : public Agent {
public:
    Move chooseMove(const Board& board) override;
    std::string name() const override { return "RandomAgent"; }
};
