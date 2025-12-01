#include "DepthAgent.hpp"
#include "../search/DepthLimited.hpp"
#include <sstream>

DepthAgent::DepthAgent(int maxDepth)
    : maxDepth(maxDepth), timeLimitMs(0), useID(false) {}

DepthAgent::DepthAgent(int maxDepth, long long timeLimitMs, bool useIterativeDeepening)
    : maxDepth(maxDepth), timeLimitMs(timeLimitMs), useID(useIterativeDeepening) {}

game::Move DepthAgent::chooseMove(const game::Board& board) {
    if (useID)
        last = search::DepthLimited::iterativeDeepening(board, maxDepth, timeLimitMs);
    else
        last = search::DepthLimited::run(board, maxDepth);

    statsCache.nodesExplored = last.nodesExplored;
    statsCache.value = last.value;
    statsCache.maxDepthReached = last.maxDepthReached;
    statsCache.isExact = last.isExact;
    statsCache.pruned = -1;

    return last.move;
}

const SearchStats* DepthAgent::stats() const {
    return &statsCache;
}

std::string DepthAgent::name() const {
    std::ostringstream os;
    os << "Depth-Limited Agent (depth=" << maxDepth << ")";
    return os.str();
}
