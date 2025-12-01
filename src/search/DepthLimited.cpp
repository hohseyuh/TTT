#include "DepthLimited.hpp"
#include "moveOrdering.hpp"
#include "Heuristics.hpp"
#include <chrono>
#include <algorithm>

using namespace std;
using namespace game;

namespace search {

int DepthLimited::nodesExplored = 0;
int DepthLimited::maxDepthReached = 0;
bool DepthLimited::foundExactValue = false;

static inline long long nowMs() {
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count();
}

int DepthLimited::depthLimitedValue(const Board& board,
                                    int depth,
                                    int alpha,
                                    int beta,
                                    bool maximizing,
                                    int currentDepth)
{
    nodesExplored++;
    maxDepthReached = max(maxDepthReached, currentDepth);

    // Terminal state
    if (auto util = Rules::utility(board)) {
        foundExactValue = true;
        int v = *util;

        // Same scaling logic as Java
        if (v > 0) return v * 1000 + depth;
        if (v < 0) return v * 1000 - depth;
        return 0;
    }

    // Depth limit
    if (depth <= 0) {
        return evaluate(board);
    }

    // Generate & order moves
    auto moves = Rules::actions(board);
    MoveOrdering::orderMoves(board, moves);

    if (maximizing) {
        int value = INT_MIN + 1000;

        for (auto mv : moves) {
            Board child = Rules::result(board, mv);
            value = max(value, depthLimitedValue(child, depth - 1,
                                                 alpha, beta, false,
                                                 currentDepth + 1));
            alpha = max(alpha, value);
            if (alpha >= beta) break;
        }

        return value;
    } else {
        int value = INT_MAX - 1000;

        for (auto mv : moves) {
            Board child = Rules::result(board, mv);
            value = min(value, depthLimitedValue(child, depth - 1,
                                                 alpha, beta, true,
                                                 currentDepth + 1));
            beta = min(beta, value);
            if (beta <= alpha) break;
        }

        return value;
    }
}

DepthLimitedResult DepthLimited::run(const Board& board, int maxDepth)
{
    nodesExplored = 0;
    maxDepthReached = 0;
    foundExactValue = false;

    auto moves = Rules::actions(board);
    if (moves.empty()) {
        return DepthLimitedResult(0, {0,0}, 0, 0, true);
    }

    MoveOrdering::orderMoves(board, moves);

    bool maximizing = (Rules::player(board) == 'X');
    int alpha = INT_MIN + 1000;
    int beta = INT_MAX - 1000;

    int bestValue = maximizing ? INT_MIN + 1000 : INT_MAX - 1000;
    game::Move bestMove = moves[0];

    for (auto mv : moves) {
        Board child = Rules::result(board, mv);

        int value = depthLimitedValue(child, maxDepth - 1,
                                      alpha, beta, !maximizing,
                                      1);

        if (maximizing) {
            if (value > bestValue) {
                bestValue = value;
                bestMove = mv;
            }
            alpha = max(alpha, bestValue);
        } else {
            if (value < bestValue) {
                bestValue = value;
                bestMove = mv;
            }
            beta = min(beta, bestValue);
        }
    }

    return DepthLimitedResult(bestValue, bestMove,
                              nodesExplored, maxDepthReached,
                              foundExactValue);
}

DepthLimitedResult DepthLimited::iterativeDeepening(const Board& board,
                                                    int maxDepth,
                                                    long long timeLimitMs)
{
    long long start = nowMs();
    DepthLimitedResult best = DepthLimitedResult();

    for (int depth = 1; depth <= maxDepth; depth++) {
        if (timeLimitMs > 0 && nowMs() - start >= timeLimitMs)
            break;

        DepthLimitedResult r = run(board, depth);
        best = r;

        if (r.isExact && abs(r.value) > 900)
            break;
    }

    return best.value != 0 ? best : run(board, 1);
}

}
