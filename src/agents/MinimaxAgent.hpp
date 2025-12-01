#pragma once
#include "Agent.hpp"

class MinimaxAgent : public Agent {
public:
    game::Move chooseMove(const game::Board& board) override;
    std::string name() const override { return "Minimax"; }

    const SearchStats* stats() const override { return &last; }

private:
    int minimax(const game::Board&, bool maximizing);

    SearchStats last;
};
