#pragma once
#include "Agent.hpp"

using namespace game;

class AlphaBetaAgent : public Agent {
public:
    Move chooseMove(const Board& board) override;
    std::string name() const override { return "AlphaBeta"; }

    const SearchStats* stats() const override { return &last; }

private:
    int alphabeta(const Board&, int alpha, int beta, bool maximizing);

    SearchStats last;
};
