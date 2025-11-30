#include "minimaxAgent.hpp"
using namespace std;
using namespace game;
using namespace search;

namespace agents {

    Move MinimaxAgent::chooseMove(const Board& board) {
        MinimaxResult result = Minimax::run(board);
        return result.move;
    }

}
