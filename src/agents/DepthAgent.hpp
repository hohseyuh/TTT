#pragma once

#include "Agent.hpp"
#include "../search/DepthLimitedResult.hpp"
#include <memory>

class DepthAgent : public Agent {
public:
    DepthAgent(int maxDepth);
    DepthAgent(int maxDepth, long long timeLimitMs, bool useIterativeDeepening);

    game::Move chooseMove(const game::Board& board) override;
    const SearchStats* stats() const override;
    std::string name() const override;

private:
    int maxDepth;
    long long timeLimitMs;
    bool useID;

    search::DepthLimitedResult last;

    mutable SearchStats statsCache;
};
