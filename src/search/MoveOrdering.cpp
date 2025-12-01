#include "moveOrdering.hpp"
#include "../game/Rules.hpp"
#include <algorithm>
#include <cmath>

using namespace std;
using namespace game;

namespace search {

    // Score adjacency to any existing stones
    static int adjacencyScore(const Board& b, const Move& mv) {
        int score = 0;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;

                int nr = mv.r + dr;
                int nc = mv.c + dc;

                if (b.inBounds(nr, nc)) {
                    char cell = b.at(nr, nc);
                    if (cell != ' ') score += 5;
                }
            }
        }
        return score;
    }

    // Score closeness to centre
    static int centerScore(const Board& b, const Move& mv) {
        int cr = b.m / 2;
        int cc = b.m / 2;
        int dist = abs(mv.r - cr) + abs(mv.c - cc);
        return -dist;
    }

    // Check whether this move becomes a winning move for the current player
    static int selfThreatScore(const Board& b, const Move& mv) {
        Board nb = Rules::result(b, mv);
        if (auto w = Rules::winner(nb)) {
            return 10000;
        }
        return 0;
    }

    // Check whether this move blocks opponent’s win
    // (without trying to manually place opponent marks)
    static int blockThreatScore(const Board& b, const Move& mv) {

        char me = Rules::player(b);
        char opp = (me == 'X' ? 'O' : 'X');

        // Simulate a board where the opponent plays this exact move if empty.
        if (!b.isEmpty(mv.r, mv.c))
            return 0;

        // To simulate an opponent move, we must use Rules::result
        // but that always plays the *current* player.
        // So we temporarily flip perspective via brute-force check:
        Board pseudo = b;

        // We need a legal opponent move: regenerate moves and test each
        // that leads to the same coords (mv.r, mv.c)
        auto oppMoves = Rules::actions(b);
        for (auto m2 : oppMoves) {
            if (m2.r == mv.r && m2.c == mv.c) {
                Board nb = Rules::result(b, m2);
                if (auto w2 = Rules::winner(nb)) {
                    if (*w2 == opp)
                        return 5000;
                }
            }
        }

        return 0;
    }

    void MoveOrdering::orderMoves(const Board& board, vector<Move>& moves) {

        // Detect whether the board is empty
        bool empty = true;
        for (int r = 0; r < board.m && empty; r++) {
            for (int c = 0; c < board.m; c++) {
                if (board.at(r, c) != ' ') {
                    empty = false;
                    break;
                }
            }
        }

        if (empty) {
            // First move: choose centre first
            int cr = board.m / 2;
            int cc = board.m / 2;

            sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
                int da = abs(a.r - cr) + abs(a.c - cc);
                int db = abs(b.r - cr) + abs(b.c - cc);
                return da < db;
            });
            return;
        }

        struct ScoredMove {
            Move mv;
            int score;
        };

        vector<ScoredMove> scored;
        scored.reserve(moves.size());

        for (auto& mv : moves) {
            int s = 0;
            s += adjacencyScore(board, mv);
            s += centerScore(board, mv);
            s += selfThreatScore(board, mv);
            s += blockThreatScore(board, mv);

            scored.push_back({mv, s});
        }

        sort(scored.begin(), scored.end(),
            [](const ScoredMove& a, const ScoredMove& b) {
                return a.score > b.score;
            });

        for (int i = 0; i < moves.size(); i++)
            moves[i] = scored[i].mv;
    }

}
