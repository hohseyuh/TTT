#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace game {

    struct Move {
        int r;
        int c;

        Move() : r(-1), c(-1) {}
        Move(int rr, int cc) : r(rr), c(cc) {}

        bool operator==(const Move& o) const noexcept { return r == o.r && c == o.c; }
        bool operator<(const Move& o) const noexcept {
            if (r != o.r) return r < o.r;
            return c < o.c;
        }
    };

    class Board {
    public:
        // Public fields for small project convenience (can be wrapped later)
        int m; // board dimension
        int k; // k-in-a-row needed to win
        vector<char> grid; // flattened row-major grid, size m*m
        // Values in grid: 'X', 'O', or ' ' (space) for empty

        // Constructors
        explicit Board(int m = 3, int k = 3);
        Board(const Board& other) = default;
        Board& operator=(const Board& other) = default;

        // Accessors
        inline int index(int r, int c) const noexcept { return r * m + c; }
        char at(int r, int c) const;
        void set(int r, int c, char p);

        // Helpers
        bool inBounds(int r, int c) const noexcept;
        bool isEmpty(int r, int c) const noexcept;
        int countEmpty() const noexcept;
        string toString() const;

        // For test
        Board place(int r, int c, char symbol) const;

    };
}