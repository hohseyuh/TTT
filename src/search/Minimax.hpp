#pragma once
#include "../game/Rules.hpp"
#include <optional>

namespace search {

struct MinimaxResult {
    int value;
    game::Move move;
};

class Minimax {
public:
    static MinimaxResult run(const game::Board& board);
};

}
