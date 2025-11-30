#include "minimax.hpp"
using namespace std;
using namespace game;

namespace search {

    static int minimaxValue(const Board& board, bool maximizing) {
        auto util = Rules::utility(board);
        if (util.has_value()) {
            return util.value();
        }

        vector<Move> moves = Rules::actions(board);

        if (maximizing) {
            int best = -1000000;
            for (const Move& mv : moves) {
                Board child = Rules::result(board, mv);
                best = max(best, minimaxValue(child, false));
            }
            return best;
        } else {
            int best = +1000000;
            for (const Move& mv : moves) {
                Board child = Rules::result(board, mv);
                best = min(best, minimaxValue(child, true));
            }
            return best;
        }
    }

    MinimaxResult Minimax::run(const Board& board) {
        vector<Move> moves = Rules::actions(board);
        bool maximizing = (Rules::player(board) == 'X');

        int bestValue = maximizing ? -1000000 : +1000000;
        Move bestMove;

        for (const Move& mv : moves) {
            Board child = Rules::result(board, mv);
            int value = minimaxValue(child, !maximizing);

            if (maximizing) {
                if (value > bestValue) {
                    bestValue = value;
                    bestMove = mv;
                }
            } else {
                if (value < bestValue) {
                    bestValue = value;
                    bestMove = mv;
                }
            }
        }
        return { bestValue, bestMove };
    }

} // namespace search
