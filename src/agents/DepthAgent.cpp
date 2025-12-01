#include "DepthAgent.hpp"
#include "../game/Rules.hpp"
#include <algorithm>

using namespace std;

int DepthAgent::heuristic(const Board& b) {
    if (auto u = Rules::utility(b)) return *u * 1000;
    return 0;
}

int DepthAgent::eval(const Board& b, int depth, bool maximizing) {
    last.nodesExplored++;
    last.maxDepthReached = max(last.maxDepthReached, depthLimit - depth);

    if (auto u = Rules::utility(b)) {
        last.isExact = true;
        return *u * 1000;
    }
    if (depth == 0) {
        last.isExact = false;
        return heuristic(b);
    }

    auto moves = Rules::actions(b);
    int best = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(b, mv);
        int v = eval(nb, depth - 1, !maximizing);

        if (maximizing) best = max(best, v);
        else            best = min(best, v);
    }

    return best;
}

Move DepthAgent::chooseMove(const Board& board) {
    last = {};

    bool maximizing = (Rules::player(board) == 'X');
    auto moves = Rules::actions(board);

    Move bestMove = moves[0];
    int bestVal = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(board, mv);
        int val = eval(nb, depthLimit, !maximizing);

        if (maximizing && val > bestVal) { bestVal = val; bestMove = mv; }
        if (!maximizing && val < bestVal) { bestVal = val; bestMove = mv; }
    }

    last.value = bestVal;
    return bestMove;
}
