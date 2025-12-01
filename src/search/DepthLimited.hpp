#pragma once

#include "../game/Board.hpp"
#include "../game/Rules.hpp"
#include "DepthLimitedResult.hpp"

namespace search {

    class DepthLimited {
    public:
        static DepthLimitedResult run(const game::Board& board, int maxDepth);
        static DepthLimitedResult iterativeDeepening(const game::Board& board,
                                                     int maxDepth,
                                                     long long timeLimitMs);

    private:
        static int depthLimitedValue(const game::Board& board,
                                     int depth,
                                     int alpha,
                                     int beta,
                                     bool maximizing,
                                     int currentDepth);

    private:
        static int nodesExplored;
        static int maxDepthReached;
        static bool foundExactValue;
    };

}
