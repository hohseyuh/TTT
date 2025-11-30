#pragma once

#include "Board.hpp"
#include <optional>

namespace game {

    /*
     * KDetector:
     * - Provides winner detection for any m, k.
     * - Returns 'X' or 'O' if a winner is found, otherwise std::nullopt.
     */
    class KDetector {
    public:
        static std::optional<char> findWinner(const Board& board) noexcept;
    };

}