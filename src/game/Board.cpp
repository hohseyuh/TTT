#include "Board.hpp"
#include <bits/stdc++.h>

using namespace std;

namespace game {

    Board::Board(int m_, int k_) : m(m_), k(k_), grid(static_cast<size_t>(m_ * m_), ' ') {
        // Validate sensible params
        if (m <= 0) throw std::invalid_argument("m must be > 0");
        if (k <= 0 || k > m) throw std::invalid_argument("k must be in 1..m");
    }

    char Board::at(int r, int c) const {
        if (!inBounds(r, c)) throw std::out_of_range("Board::at out of bounds");
        return grid[static_cast<size_t>(index(r, c))];
    }

    void Board::set(int r, int c, char p) {
        if (!inBounds(r, c)) throw std::out_of_range("Board::set out of bounds");
        if (p != 'X' && p != 'O' && p != ' ') throw std::invalid_argument("Invalid player char");
        grid[static_cast<size_t>(index(r, c))] = p;
    }

    bool Board::inBounds(int r, int c) const noexcept {
        return r >= 0 && r < m && c >= 0 && c < m;
    }

    bool Board::isEmpty(int r, int c) const noexcept {
        return inBounds(r, c) && grid[static_cast<size_t>(index(r, c))] == ' ';
    }

    int Board::countEmpty() const noexcept {
        return static_cast<int>(std::count(grid.begin(), grid.end(), ' '));
    }

    std::string Board::toString() const {
        std::ostringstream oss;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < m; ++c) {
                char ch = at(r, c);
                if (ch == ' ') oss << '.';
                else oss << ch;
                if (c + 1 < m) oss << ' ';
            }
            if (r + 1 < m) oss << '\n';
        }
        return oss.str();
    }

    Board Board::place(int r, int c, char symbol) const {
        Board copy = *this;
        copy.set(r, c, symbol);   // or whatever setter you have
        return copy;
    }


} // namespace game
