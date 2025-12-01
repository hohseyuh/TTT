#pragma once
#include "../game/Board.hpp"

namespace search {

    struct DepthLimitedResult {
        int value;
        game::Move move;
        int nodesExplored;
        int maxDepthReached;
        bool isExact;

        DepthLimitedResult()
            : value(0), move({0,0}), nodesExplored(0),
              maxDepthReached(0), isExact(false) {}

        DepthLimitedResult(int value, game::Move move,
                           int nodesExplored, int maxDepthReached,
                           bool isExact)
            : value(value), move(move), nodesExplored(nodesExplored),
              maxDepthReached(maxDepthReached), isExact(isExact) {}
    };

}
