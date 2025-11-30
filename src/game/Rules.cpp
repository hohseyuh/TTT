#include "Rules.hpp"
#include <stdexcept>

using namespace std;
using namespace Rules;

namespace game {

Board initialState(int m, int k) {
    return Board(m, k);
}

char player(const Board& b) noexcept {
    int xCount = 0;
    int oCount = 0;
    for (char ch : b.grid) {
        if (ch == 'X') ++xCount;
        else if (ch == 'O') ++oCount;
    }
    // X moves first. If counts are equal -> X to move, otherwise O
    return (xCount == oCount) ? 'X' : 'O';
}

vector<Move> actions(const Board& b) noexcept {
    vector<Move> out;
    out.reserve(static_cast<size_t>(b.countEmpty()));
    for (int r = 0; r < b.m; ++r) {
        for (int c = 0; c < b.m; ++c) {
            if (b.isEmpty(r, c)) out.emplace_back(r, c);
        }
    }
    // Emitted in row-major order -> lexicographic (r,c)
    return out;
}

Board result(const Board& b, const Move& action) {
    if (!b.inBounds(action.r, action.c)) throw invalid_argument("Action out of bounds");
    if (!b.isEmpty(action.r, action.c)) throw invalid_argument("Action on non-empty cell");
    Board nb = b;
    char p = player(b);
    nb.set(action.r, action.c, p);
    return nb;
}

optional<char> winner(const Board& b) noexcept {
    return KDetector::find_winner(b);
}

bool terminal(const Board& b) noexcept {
    if (winner(b).has_value()) return true;
    return (b.countEmpty() == 0);
}

optional<int> utility(const Board& b) noexcept {
    auto w = winner(b);
    if (!w.has_value()) {
        if (b.countEmpty() == 0) return 0; // draw
        return nullopt;
    }
    return (w.value() == 'X') ? 1 : -1;
}

}