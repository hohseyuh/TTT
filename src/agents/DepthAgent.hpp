#pragma once
#include "agent.hpp"
#include "../search/depthLimited.hpp"

namespace agents {

    class DepthAgent : public Agent {
    public:
        explicit DepthAgent(int depthLimit);

        Move chooseMove(const Board& board) override;

    private:
        int depth;
    };

}
