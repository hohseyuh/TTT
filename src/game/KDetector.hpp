#pragma once
#include "Board.hpp"
#include <optional>

using namespace std;

namespace game {

/*
 * KDetector:
 * - Provides winner detection for any m, k.
 * - Returns 'X' or 'O' if a winner is found, otherwise std::nullopt.
 */

class KDetector {
public:
    static optional<char> findWinner(const Board& board) noexcept;
};

} 