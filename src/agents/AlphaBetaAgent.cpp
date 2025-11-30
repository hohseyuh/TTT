#include "alphaBetaAgent.hpp"
using namespace std;
using namespace game;
using namespace search;

namespace agents {

    Move AlphaBetaAgent::chooseMove(const Board& board) {
        AlphaBetaResult result = AlphaBeta::run(board);
        return result.move;
    }

}
