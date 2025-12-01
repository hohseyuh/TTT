#pragma once
#include <string>
#include "../game/Board.hpp"
#include "SearchStats.hpp"

class Agent {
public:
    virtual ~Agent() = default;

    virtual game::Move chooseMove(const game::Board& board) = 0;
    virtual std::string name() const = 0;

    virtual const SearchStats* stats() const { return nullptr; }
};
