#include "KDetector.hpp"
#include <vector>

using namespace std;
using namespace KDetector;

namespace game {

static inline optional<char> checkLine(const vector<char>& line, int k) {
    int n = static_cast<int>(line.size());
    if (k <= 0 || n < k) return nullopt;

    int count = 0;
    char last = ' ';
    for (int i = 0; i < n; ++i) {
        char cur = line[i];
        if (cur != ' ' && cur == last) {
            ++count;
        } else {
            last = cur;
            count = (cur == ' ') ? 0 : 1;
        }
        if (last != ' ' && count >= k) return last;
    }
    return nullopt;
}

optional<char> findWinner(const Board& board) noexcept {
    const int m = board.m;
    const int k = board.k;

    // Check rows
    for (int r = 0; r < m; ++r) {
        vector<char> row;
        row.reserve(m);
        for (int c = 0; c < m; ++c) row.push_back(board.at(r,c));
        if (auto w = checkLine(row, k)) return w;
    }

    // Check columns
    for (int c = 0; c < m; ++c) {
        vector<char> col;
        col.reserve(m);
        for (int r = 0; r < m; ++r) col.push_back(board.at(r,c));
        if (auto w = checkLine(col, k)) return w;
    }

    // Check diagonals (r - c = const)
    for (int d = -(m - 1); d <= (m - 1); ++d) {
        vector<char> diag;
        for (int r = 0; r < m; ++r) {
            int c = r - d;
            if (c >= 0 && c < m) diag.push_back(board.at(r, c));
        }

        // Oversize diagonals are not checked
        if (static_cast<int>(diag.size()) >= k) {
            if (auto w = checkLine(diag, k)) return w;
        }
    }

    // Check anti-diagonals (r + c = const)
    for (int s = 0; s <= 2*(m-1); ++s) {
        vector<char> adiag;
        for (int r = 0; r < m; ++r) {
            int c = s - r;
            if (c >= 0 && c < m) adiag.push_back(board.at(r, c));
        }

        // Oversize...
        if (static_cast<int>(adiag.size()) >= k) {
            if (auto w = checkLine(adiag, k)) return w;
        }
    }

    return nullopt;
}

}
