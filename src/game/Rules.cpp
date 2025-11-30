#include "Rules.hpp"
#include <bits/stdc++.h>

namespace game {
    Board Rules::initialState(int m, int k) {
        return Board(m, k);
    }

    char Rules::player(const Board& b) noexcept {
        int x_count = 0;
        int o_count = 0;
        for (char ch : b.grid) {
            if (ch == 'X') ++x_count;
            else if (ch == 'O') ++o_count;
        }
        // X moves first. If counts are equal -> X to move, otherwise O
        return (x_count == o_count) ? 'X' : 'O';
    }

    std::vector<Move> Rules::actions(const Board& b) noexcept {
        std::vector<Move> out;
        out.reserve(static_cast<size_t>(b.countEmpty()));
        for (int r = 0; r < b.m; ++r) {
            for (int c = 0; c < b.m; ++c) {
                if (b.isEmpty(r, c)) out.emplace_back(r, c);
            }
        }
        // Emitted in row-major order -> lexicographic (r,c)
        return out;
    }

    Board Rules::result(const Board& b, const Move& action) {
        if (!b.inBounds(action.r, action.c)) throw std::invalid_argument("Action out of bounds");
        if (!b.isEmpty(action.r, action.c)) throw std::invalid_argument("Action on non-empty cell");
        Board nb = b;
        char p = player(b);
        nb.set(action.r, action.c, p);
        return nb;
    }

    std::optional<char> Rules::winner(const Board& b) noexcept {
        return KDetector::findWinner(b);
    }

    bool Rules::terminal(const Board& b) noexcept {
        if (winner(b).has_value()) return true;
        return (b.countEmpty() == 0);
    }

    std::optional<int> Rules::utility(const Board& b) noexcept {
        auto w = winner(b);
        if (!w.has_value()) {
            if (b.countEmpty() == 0) return 0; // draw
            return std::nullopt;
        }
        return (w.value() == 'X') ? 1 : -1;
    }
}