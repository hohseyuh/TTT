#include "alphaBeta.hpp"
using namespace std;
using namespace game;

namespace search {

static int alphaBetaValue(const Board& board, int alpha, int beta, bool maximizing) {
    auto util = utility(board);
    if (util.has_value()) return util.value();

    vector<Move> moves = actions(board);

    if (maximizing) {
        int value = -1000000;
        for (const Move& mv : moves) {
            Board child = result(board, mv);
            value = max(value, alphaBetaValue(child, alpha, beta, false));
            alpha = max(alpha, value);
            if (alpha >= beta) break; // prune
        }
        return value;
    } else {
        int value = +1000000;
        for (const Move& mv : moves) {
            Board child = result(board, mv);
            value = min(value, alphaBetaValue(child, alpha, beta, true));
            beta = min(beta, value);
            if (beta <= alpha) break; // prune
        }
        return value;
    }
}

AlphaBetaResult run(const Board& board) {
    vector<Move> moves = actions(board);
    bool maximizing = (player(board) == 'X');

    int alpha = -1000000;
    int beta  = +1000000;
    int bestValue = maximizing ? -1000000 : +1000000;
    Move bestMove;

    for (const Move& mv : moves) {
        Board child = Rules::result(board, mv);
        int value = alphaBetaValue(child, alpha, beta, !maximizing);

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