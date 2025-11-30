#pragma once

#include "Board.hpp"
#include "KDetector.hpp"
#include <vector>
#include <optional>

using namespace std;

namespace game {

/*
 * Rules provides the functions specified by the assignment:
 * - initial_state(m,k)
 * - player(board)
 * - actions(board)
 * - result(board, action)
 * - winner(board)
 * - terminal(board)
 * - utility(board)
 */

class Rules {
public:
    static Board initial_state(int m, int k);

    // Returns 'X' or 'O' for whose turn it is. X moves first.
    static char player(const Board& b) noexcept;

    // Returns legal moves (empty cells) in lexicographic order (row, col).
    static vector<Move> actions(const Board& b) noexcept;

    // Returns a new Board after applying action. Throws if illegal.
    static Board result(const Board& b, const Move& action);

    // Returns 'X' or 'O' if winner exists, otherwise std::nullopt.
    static optional<char> winner(const Board& b) noexcept;

    // True if terminal (win or draw)
    static bool terminal(const Board& b) noexcept;

    // Utility: +1 if X wins, -1 if O wins, 0 if draw, std::nullopt if non-terminal.
    static optional<int> utility(const Board& b) noexcept;
};

}