#include "moveOrdering.hpp"
using namespace std;
using namespace game;

namespace search {

    void MoveOrdering::orderMoves(const Board& board, vector<Move>& moves) {
        // Simple fallback: center, corners, edges.
        int m = board.m;
        pair center = {m/2, m/2};

        sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b){
            auto dist = [&](const Move& mv) {
                return abs(mv.r - center.first) + abs(mv.c - center.second);
            };
            return dist(a) < dist(b);
        });
    }

}