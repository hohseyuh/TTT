#include "depthLimited.hpp"
using namespace std;
using namespace game;

namespace search {

static int depthSearch(const Board& board, int depth, int alpha, int beta, bool maximizing) {

    if (depth == 0) {
        return Heuristics::evaluate(board);
    }

    auto util = Rules::utility(board);
    if (util.has_value()) return util.value();

    vector<Move> moves = Rules::actions(board);
    MoveOrdering::orderMoves(board, moves);

    if (maximizing) {
        int best = -1000000;
        for (const Move& mv : moves) {
            Board child = Rules::result(board, mv);
            best = max(best, depthSearch(child, depth - 1, alpha, beta, false));
            alpha = max(alpha, best);
            if (alpha >= beta) break;
        }
        return best;
    }
    int best = +1000000;
    for (const Move& mv : moves) {
        Board child = Rules::result(board, mv);
        best = min(best, depthSearch(child, depth - 1, alpha, beta, true));
        beta = min(beta, best);
        if (beta <= alpha) break;
    }
    return best;
}

DepthSearchResult DepthLimited::run(const Board& board, int depth) {
    vector<Move> moves = Rules::actions(board);
    bool maximizing = (Rules::player(board) == 'X');

    MoveOrdering::orderMoves(board, moves);

    int alpha = -1000000;
    int beta  = +1000000;

    int bestValue = maximizing ? -1000000 : +1000000;
    Move bestMove;

    for (const Move& mv : moves) {
        Board child = Rules::result(board, mv);
        int value = depthSearch(child, depth - 1, alpha, beta, !maximizing);

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

    return { bestValue, bestMove };
}

}