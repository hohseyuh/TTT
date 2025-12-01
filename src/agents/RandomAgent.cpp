#include "RandomAgent.hpp"
#include "../game/Rules.hpp"
#include <random>

using namespace game;

Move RandomAgent::chooseMove(const Board& board) {
    auto moves = Rules::actions(board);
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    return moves[dist(rng)];
}
