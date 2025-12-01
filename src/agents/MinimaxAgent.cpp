#include "MinimaxAgent.hpp"
#include "../game/Rules.hpp"

using namespace game;

int MinimaxAgent::minimax(const Board& b, bool maximizing) {
    last.nodesExplored++;

    if (auto u = Rules::utility(b))
        return *u;

    auto moves = Rules::actions(b);
    int best = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(b, mv);
        int val = minimax(nb, !maximizing);
        if (maximizing) best = std::max(best, val);
        else            best = std::min(best, val);
    }

    return best;
}

Move MinimaxAgent::chooseMove(const Board& board) {
    last = {};

    bool maximizing = (Rules::player(board) == 'X');

    auto moves = Rules::actions(board);
    Move bestMove = moves[0];
    int bestVal = maximizing ? -999999 : 999999;

    for (auto mv : moves) {
        Board nb = Rules::result(board, mv);
        int val = minimax(nb, !maximizing);

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
