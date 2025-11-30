#include "depthAgent.hpp"
using namespace std;
using namespace game;
using namespace search;

namespace agents {

    DepthAgent::DepthAgent(int depthLimit) : depth(depthLimit) {}

    Move DepthAgent::chooseMove(const Board& board) {
        DepthSearchResult result = DepthLimited::run(board, depth);
        return result.move;
    }

}
