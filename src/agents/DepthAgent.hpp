#pragma once
#include "Agent.hpp"

using namespace game;

class DepthAgent : public Agent {
public:
    explicit DepthAgent(int depth) : depthLimit(depth) {}

    Move chooseMove(const Board& board) override;
    std::string name() const override { return "DepthLimited"; }
    const SearchStats* stats() const override { return &last; }

private:
    int eval(const Board& b, int depth, bool maximizing);
    int heuristic(const Board&);

    int depthLimit;
    SearchStats last;
};
