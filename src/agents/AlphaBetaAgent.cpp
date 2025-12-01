#include "AlphaBetaAgent.hpp"
#include "../game/Rules.hpp"

using namespace std;

int AlphaBetaAgent::alphabeta(const Board& b, int alpha, int beta, bool maximizing) {
    last.nodesExplored++;

    if (auto u = Rules::utility(b))
        return *u;

    auto moves = Rules::actions(b);
    int value = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(b, mv);
        int v = alphabeta(nb, alpha, beta, !maximizing);

        if (maximizing) {
            value = max(value, v);
            alpha = max(alpha, value);
        } else {
            value = min(value, v);
            beta = min(beta, value);
        }

        if (beta <= alpha) {
            last.pruned++;
            break;
        }
    }
    return value;
}

Move AlphaBetaAgent::chooseMove(const Board& board) {
    last = {};
    last.pruned = 0;

    bool maximizing = (Rules::player(board) == 'X');
    auto moves = Rules::actions(board);

    Move bestMove = moves[0];
    int bestVal = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(board, mv);

        int val = alphabeta(nb, -999999, 999999, !maximizing);

        if (maximizing && val > bestVal) {
            bestVal = val;
            bestMove = mv;
        }
        if (!maximizing && val < bestVal) {
            bestVal = val;
            bestMove = mv;
        }
    }

    last.value = bestVal;
    return bestMove;
}
